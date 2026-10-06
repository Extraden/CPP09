#include "BitcoinExchange.hpp"
#include <cstddef>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <iostream>
#include <cctype>

BitcoinExchange::BitcoinExchange() {}

BitcoinExchange::BitcoinExchange(const BitcoinExchange& other) : rates(other.rates) {}

BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
    rates = other.rates;
	return *this;
}

BitcoinExchange::~BitcoinExchange() {}


void BitcoinExchange::loadDatabase(const std::string& database)
{
  std::ifstream data(database.c_str());

  //TODO exceptions
  
  if (!data.is_open())
    throw std::runtime_error("Database can't open");

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
}

static bool is_valid_date(std::string& date)
{
  if (date.length() != 10)
    return false;


  for (std::size_t i = 0; i < date.size(); ++i)
  {
    if (i == 4 || i == 7)
    {
      if (date[4] != '-' || date[7] != '-')
        return false;
      else
       continue;
    }
    if (!std::isdigit(static_cast<unsigned int>(date[i])))
      return false;
  }
  return true;
}


static bool is_line_valid(std::string& line)
{
  std::istringstream iss(line);

  std::string date;
  std::string value;

  std::size_t sep = line.find("|");
  if (sep == std::string::npos)
    return false;


  if (!is_valid_date(date))
    return false;

  return true;
}

void  BitcoinExchange::exchange(const char *input)
{
  std::ifstream file(input);

  if (!file)
    throw std::runtime_error("Error opening file!");

  std::string line;

  std::getline(file, line);
  //TODO check first line


  while (std::getline(file, line))
  {
    if (is_line_valid(line))
      std::cout << line;
  }


}
