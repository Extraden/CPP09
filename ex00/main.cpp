#include <iostream>
#include <string>
#include "BitcoinExchange.hpp"

int	main(int argc, char *argv[])
{
	(void)argv;

	if (argc != 2)
	{
		std::cout << "Wrong input!\nUsage:\n./btc input.txt\n";
    return 0;
	}


  BitcoinExchange btc;

  btc.loadDatabase("data.csv");

	return 0;
}
