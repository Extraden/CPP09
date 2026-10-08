#include <iostream>
#include "RPN.hpp"

int	main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Pass RPN expression as an argument\n";
    return 1;
  }

  try 
  {
    int result = solve(argv[1]);
    std::cout << result << "\n";
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << "\n";
    return 1;
  }
	return 0;
}
