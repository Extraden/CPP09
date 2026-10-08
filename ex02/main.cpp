#include <vector>
#include <iostream>
#include "PmergeMe.hpp"

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
  }
	return 0;
}
