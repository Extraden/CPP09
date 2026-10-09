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

  fordJohnson(numbers);
	return 0;
}
