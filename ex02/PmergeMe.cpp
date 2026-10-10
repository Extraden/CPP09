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

  for (std::size_t i = 0; i < items.size(); i = i + 2)
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
    
    pairs[i].small.id = i;
    pairs[i].big.id = i;
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

void insertPending(std::vector<Item>& mainChain, std::vector<Item>& pending)
{
  mainChain.insert(mainChain.begin(), pending[0]);
  if (pending.size() == 1)
    return;

  for (std::vector<Item>::iterator it = pending.begin() + 1; it != pending.end(); ++it) //TODO replace regular loop with Jacobstahl sequence
    binaryInsert(mainChain, *it, mainChain.begin() + 1, mainChain.end());

}

void  fordJohnson(std::vector<Item>& items)
{
  if (items.size() <= 1)
    return;

  std::vector<Pair> pairs;
  fillPairs(pairs, items);
  sortPairs(pairs);

  std::vector<Item> winners;
  std::vector<Item> pending;

  for (std::size_t i = 0; i < pairs.size(); ++i)
  {
    winners.push_back(pairs[i].big);
    pending.push_back(pairs[i].small);
    std::cout << winners[i].value << " ";
    if (i == pairs.size() - 1)
      std::cout << "\n";
  }

  fordJohnson(winners);
  insertPending(winners, pending);
  
  for (std::size_t i = 0; i < winners.size(); ++i)
  {
    std::cout << winners[i].value << " ";
    if (i == winners.size() - 1)
      std::cout << "\n";
  }
}

