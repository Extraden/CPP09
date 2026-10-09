#include "PmergeMe.hpp"
#include <vector>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <stdexcept>
#include <iostream>

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

static std::vector<Item> intsToItems(const std::vector<int>& v)
{
  std::vector<Item> items;

  for (std::size_t i = 0; i < v.size(); ++i)
  {
    Item item;
    item.id = i;
    item.value = v[i];
    items.push_back(item);
  }
  return items;
}

void  sortPairs(std::vector<Pair>& pairs)
{

  for (std::size_t i = 0; i < pairs.size(); ++i)
  {
    if (pairs[i].small.value > pairs[i].big.value)
      std::swap(pairs[i].small, pairs[i].big);
    
    pairs[i].small.id = i * 2;
    pairs[i].big.id = pairs[i].small.id + 1;
  }
}

void  fordJohnson(const std::vector<int>& winners)
{
  if (winners.size() <= 1)
    return;

  const std::vector<Item> items = intsToItems(winners);
  std::vector<Pair> pairs;

  for (std::size_t i = 0; i < items.size(); i = i + 2)
  {
    Pair pair;

    pair.small = items[i];
    pair.big = items[i + 1];
    //TODO fix if odd amount if items
    pairs.push_back(pair);
  }

  sortPairs(pairs);
  std::vector<int> newWinners;

  for (std::size_t i = 0; i < pairs.size(); ++i)
  {
    newWinners.push_back(pairs[i].big.value);
    std::cout << newWinners[i] << " ";
    if (i == pairs.size() - 1)
      std::cout << "\n";
  }

  fordJohnson(newWinners);
}

