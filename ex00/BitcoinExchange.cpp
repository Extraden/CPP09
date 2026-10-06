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

    if (!(iss >> price))
      continue;

    rates[date] = price;
  }
}

static bool is_date_valid(std::string& date)
{
  if (date.length() != 10)
  {
    std::cout << date.length() << "\n";
    return false;
  }


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

int  parseLine(std::string& line, std::string& date, double& rate)
{


    return 0;
}

static bool is_line_valid(std::string& line)
{
  std::istringstream iss(line);

  std::string value;

  std::size_t sep = line.find("|");
  if (sep == std::string::npos || line[sep - 1] != ' ')
  {
    std::cout << "Error: bad input => " << line << "\n";
    return false;
  }


  std::string date = line.substr(0, sep - 1);
  if (!is_date_valid(date))
    return false;

  return true;
}

void  BitcoinExchange::exchange(const char *input)
{
  std::ifstream file(input);

  if (!file)
    throw std::runtime_error("Error opening file!");

  std::string line;


  while (std::getline(file, line))
  {
    if (line == "data | value")
      continue;

    std::string date;
    double value;

    if (parseLine(line, date, value))
      continue;
  }


}
