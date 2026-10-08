#include <cstddef>
#include <vector>
#include <iostream>
#include "PmergeMe.hpp"

std::vector<Item> intsToItems(std::vector<int>& v)
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

int	main(int argc, char *argv[])
{
  std::vector<int> numbers;

  try 
  {
    parseArguments(argc, argv, numbers);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }


  for (std::size_t i = 0; i < numbers.size(); ++i)
  {
    std::cout << numbers[i] << " ";
    std::cout << "\n\n";
  }

  const std::vector<Item> items = intsToItems(numbers);

  for (std::size_t i = 0; i < numbers.size(); ++i)
  {
    std::cout << "id: " << items[i].id << "\nValue: " << items[i].value <<  "\n";
  }
  fordJohnson(items);
	return 0;
}
