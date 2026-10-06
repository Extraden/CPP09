#include <iostream>
#include <string>
#include "BitcoinExchange.hpp"
#include <stdexcept>

int	main(int argc, char *argv[])
{
	(void)argv;

	if (argc != 2)
	{
		std::cout << "Wrong input!\nUsage:\n./btc input.txt\n";
    return 0;
	}


  BitcoinExchange btc;

  try 
  {
    btc.loadDatabase(DATABASE);
    btc.exchange(argv[1]);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
  }

	return 0;
}
