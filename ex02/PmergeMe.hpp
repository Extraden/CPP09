#ifndef PMERGEME_HPP
# define PMERGEME_HPP

#include <vector>
#include <deque>

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

// Vector

void  parseArguments(int argc, char *argv[], std::vector<int>& v);
void  fordJohnson(std::vector<Item>& items);
std::vector<Item> intsToItems(std::vector<int>& v);
void  fillPairs(std::vector<Pair>& pairs, std::vector<Item>& items);
void  binaryInsert(std::vector<Item>& mainChain, Item& item, std::vector<Item>::iterator first, std::vector<Item>::iterator last);

// Deque

void  parseArguments(int argc, char *argv[], std::deque<int>& v);
void  fordJohnson(std::deque<Item>& items);
std::deque<Item> intsToItems(std::deque<int>& v);
void  fillPairs(std::deque<Pair>& pairs, std::deque<Item>& items);
void  binaryInsert(std::deque<Item>& mainChain, Item& item, std::deque<Item>::iterator first, std::deque<Item>::iterator last);

#endif
