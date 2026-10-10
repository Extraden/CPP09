#include "PmergeMe.hpp"
#include <cstddef>
#include <vector>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <iostream>

std::vector<int> result;

std::vector<Item> intsToItems(std::vector<int>& v)
{
  std::vector<Item> items;
  for (std::size_t i = 0; i < v.size(); ++i)
  {
    Item item;
    item.value = v[i];
    item.id = i;
    items.push_back(item);
  }
  return items;

}

void  fillPairs(std::vector<Pair>& pairs, std::vector<Item>& items)
{

  for (std::size_t i = 0; i + 1 < items.size(); i += 2)
  {
    Pair pair;

    pair.small = items[i];
    pair.big = items[i + 1];
    //TODO fix if odd amount if items
    pairs.push_back(pair);
  }
}

int jacobStahl(int n)
{
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  return (jacobStahl(n - 1) + 2 * jacobStahl(n - 2));
}

void  parseArguments(int argc, char *argv[], std::vector<int>& v)
{
  int i = 1;

  while (i < argc)
  {
    std::istringstream iss(argv[i]);
    std::string token;

    while (iss >> token)
    {
      errno = 0;
      char *end;

      long value = std::strtol(token.c_str(), &end, 10);

      if (token.c_str() == end || *end != '\0' || value <= 0 || value > INT_MAX
          || errno == ERANGE)
        throw std::runtime_error("Error");
      v.push_back(value);
    }
    i++;
  }
  if (v.empty())
    throw std::runtime_error("Error");
}

void  sortPairs(std::vector<Pair>& pairs)
{
  for (std::size_t i = 0; i < pairs.size(); ++i)
  {
    if (pairs[i].small.value > pairs[i].big.value)
      std::swap(pairs[i].small, pairs[i].big);
  }
}

void  binaryInsert(std::vector<Item>& mainChain, Item& item, std::vector<Item>::iterator first, std::vector<Item>::iterator last)
{

  while (first < last)
  {
    std::vector<Item>::iterator middle = first + (last - first) / 2;

    if (item.value < middle->value)
      last = middle;
    else
      first = middle + 1;
  }
      mainChain.insert(first, item);
}

void insertPending(std::vector<Item>& mainChain, std::vector<Item>& pending, std::vector<Pair>& pairs)
{
    mainChain.insert(mainChain.begin(), pending[0]);

    for (std::size_t i = 1; i < pending.size(); ++i)
    {
      std::vector<Item>::iterator last = mainChain.end();

      for (std::size_t j = 0; j < pairs.size(); ++j)
      {
        if (pairs[i].small.id == pending[i].id)
        {
          for (std::vector<Item>::iterator it = mainChain.begin(); it != mainChain.end(); ++it)
          {
            if (it->id == pairs[j].big.id)
            {
              last = it;
              break;
            }
          }
        }
      }

        binaryInsert(mainChain, pending[i], mainChain.begin(), last);
    }
}

void  fordJohnson(std::vector<Item>& items)
{
  if (items.size() <= 1)
    return;

  bool hasOdd = (items.size() % 2 != 0);
  Item odd;

  if (hasOdd)
    odd = items.back();

  std::vector<Pair> pairs;
  fillPairs(pairs, items);
  sortPairs(pairs);

  std::vector<Item> winners;

  for (std::size_t i = 0; i < pairs.size(); ++i)
    winners.push_back(pairs[i].big);

  fordJohnson(winners);

  std::vector<Item> pending;

  for (std::size_t i = 0; i < winners.size(); ++i)
  {
    for (std::size_t j = 0; j < pairs.size(); ++j)
      if (winners[i].id == pairs[j].big.id)
      {
        pending.push_back(pairs[j].small);
        break;
      }
  }

  if (hasOdd)
    pending.push_back(odd);

  insertPending(winners, pending, pairs);

  items.swap(winners);
}

