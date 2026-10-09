#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>

struct Item
{
  int value;
  std::size_t id;
};

struct Pair
{
  Item small;
  Item big;
};

void  parseArguments(int argc, char *argv[], std::vector<int>& v);
void  fordJohnson(const std::vector<int>& items);

#endif
