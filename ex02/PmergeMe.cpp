#include "PmergeMe.hpp"
#include <cstddef>
#include <vector>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <deque>


// ============================================== Vector ==================================================================

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

void insertOne(std::vector<Item>& mainChain, Item& item, std::vector<Pair>& pairs)
{
    std::vector<Item>::iterator last = mainChain.end();

    for (std::size_t j = 0; j < pairs.size(); ++j)
    {
        if (pairs[j].small.id == item.id)
        {
            for (std::vector<Item>::iterator it = mainChain.begin();
                 it != mainChain.end(); ++it)
            {
                if (it->id == pairs[j].big.id)
                {
                    last = it;
                    break;
                }
            }
            break;
        }
    }

    binaryInsert(mainChain, item, mainChain.begin(), last);
}
void insertPending(std::vector<Item>& mainChain, std::vector<Item>& pending, std::vector<Pair>& pairs)
{
    mainChain.insert(mainChain.begin(), pending[0]);

    std::size_t previous = 1;
    int k = 3;

    while (previous < pending.size())
    {
        std::size_t current = jacobStahl(k);

        if (current > pending.size())
            current = pending.size();

        for (std::size_t i = current; i > previous; --i)
            insertOne(mainChain, pending[i - 1], pairs);

        previous = current;
        ++k;
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


// ====================================== Deque ==========================================================



std::deque<Item> intsToItems(std::deque<int>& v)
{
  std::deque<Item> items;
  for (std::size_t i = 0; i < v.size(); ++i)
  {
    Item item;
    item.value = v[i];
    item.id = i;
    items.push_back(item);
  }
  return items;

}

void  fillPairs(std::deque<Pair>& pairs, std::deque<Item>& items)
{

  for (std::size_t i = 0; i + 1 < items.size(); i += 2)
  {
    Pair pair;

    pair.small = items[i];
    pair.big = items[i + 1];
    pairs.push_back(pair);
  }
}

void  parseArguments(int argc, char *argv[], std::deque<int>& v)
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

void  sortPairs(std::deque<Pair>& pairs)
{
  for (std::size_t i = 0; i < pairs.size(); ++i)
  {
    if (pairs[i].small.value > pairs[i].big.value)
      std::swap(pairs[i].small, pairs[i].big);
  }
}

void  binaryInsert(std::deque<Item>& mainChain, Item& item, std::deque<Item>::iterator first, std::deque<Item>::iterator last)
{

  while (first < last)
  {
    std::deque<Item>::iterator middle = first + (last - first) / 2;

    if (item.value < middle->value)
      last = middle;
    else
      first = middle + 1;
  }
      mainChain.insert(first, item);
}

void insertOne(std::deque<Item>& mainChain, Item& item, std::deque<Pair>& pairs)
{
    std::deque<Item>::iterator last = mainChain.end();

    for (std::size_t j = 0; j < pairs.size(); ++j)
    {
        if (pairs[j].small.id == item.id)
        {
            for (std::deque<Item>::iterator it = mainChain.begin();
                 it != mainChain.end(); ++it)
            {
                if (it->id == pairs[j].big.id)
                {
                    last = it;
                    break;
                }
            }
            break;
        }
    }

    binaryInsert(mainChain, item, mainChain.begin(), last);
}
void insertPending(std::deque<Item>& mainChain, std::deque<Item>& pending, std::deque<Pair>& pairs)
{
    mainChain.insert(mainChain.begin(), pending[0]);

    std::size_t previous = 1;
    int k = 3;

    while (previous < pending.size())
    {
        std::size_t current = jacobStahl(k);

        if (current > pending.size())
            current = pending.size();

        for (std::size_t i = current; i > previous; --i)
            insertOne(mainChain, pending[i - 1], pairs);

        previous = current;
        ++k;
    }
}

void  fordJohnson(std::deque<Item>& items)
{
  if (items.size() <= 1)
    return;

  bool hasOdd = (items.size() % 2 != 0);
  Item odd;

  if (hasOdd)
    odd = items.back();

  std::deque<Pair> pairs;
  fillPairs(pairs, items);
  sortPairs(pairs);

  std::deque<Item> winners;

  for (std::size_t i = 0; i < pairs.size(); ++i)
    winners.push_back(pairs[i].big);

  fordJohnson(winners);

  std::deque<Item> pending;

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


