#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : rates(other.rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
    rates = other.rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}


int BitcoinExchange::loadDatabase(const std::string& database)
{
  std::ifstream data(database.c_str());

  if (!data.is_open())
    return 1;

  std::string line;

  while (std::getline(data, line))
  {
    std::size_t comma = line.find(',');

    if (comma == std::string::npos)
      continue;
  
    std::string date = line.substr(0, comma);
    std::string priceStr = line.substr(comma + 1);

    std::stringstream iss(priceStr);

    double price;
    iss >> price;

    rates[date] = price;

  }
  return 0;
}
