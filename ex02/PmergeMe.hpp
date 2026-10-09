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
void  fordJohnson(std::vector<Item>& items);
std::vector<Item> intsToItems(std::vector<int>& v);
void  fillPairs(std::vector<Pair>& pairs, std::vector<Item>& items);
void  binaryInsert(std::vector<Item>& mainChain, Item& pending, std::size_t end);

#endif
