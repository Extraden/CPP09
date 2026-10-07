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

  int year;
  char sep1;
  int month;
  char sep2;
  int day;
  int daysInMonths[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  std::stringstream iss(date);
  iss >> year >> sep1 >> month >> sep2 >> day;
  if (!iss)
  {
    std::cout << "Error: can't parse date.\n";
    return false;
  }

  if (year < 0)
  {
    std::cout << "Error: year is negative.\n";
    return false;
  }

  if (month == 2)
  {
    if (year % 400 == 0)
      daysInMonths[1] = 29;
    else if (year % 100 == 0)
      daysInMonths[1] = 28;
    else if (year % 4 == 0)
      daysInMonths[1] = 29;
    else
      daysInMonths[1] = 28;
  }

  if (month <= 0 || month > 12)
  {
    std::cout << "Error: wrong month.\n";
    return false;
  }

  if (day <= 0 || day > daysInMonths[month - 1])
  {
    std::cout << "Error: wrong day.\n";
    return false;
  }
  return true;
}

int  BitcoinExchange::parseLine(std::string& line, std::string& date, double& rate)
{
  std::size_t sep = line.find("|");
  if (sep == std::string::npos || line[sep - 1] != ' ')
  {
    std::cout << "Error: bad input => " << line << ".\n";
    return 1;
  }

  date = line.substr(0, sep - 1);
  if (!is_date_valid(date))
    return 1;

  std::string rateStr = line.substr(sep + 1);


  std::stringstream iss(rateStr);

  if (!(iss >> rate))
  {
    std::cout << "Error: couldn't parse value.\n";
    return 1;
  }

  char extra;

  if (iss >> extra)
  {
    std::cout << "Error: value has wrong characters.\n";
    return 1;
  }

  if (rate < 0)
  {
    std::cout << "Error: not a positive number.\n";
    return 1;
  }

  if  (rate > 1000)
  {
    std::cout << "Error: too large a number.\n";
    return 1;
  }

  return 0;
}

void  BitcoinExchange::exchange(const char *input)
{
  std::ifstream file(input);

  if (!file)
    throw std::runtime_error("Error opening file!");

  std::string line;

  if (!std::getline(file, line))
    throw std::runtime_error("Error: empty file!");

  
  if (!(line == "date | value"))
    throw std::runtime_error("Error: no header!");

  while (std::getline(file, line))
  {
    std::string date;
    double value;

    if (parseLine(line, date, value))
      continue;

    std::map<std::string, double>::const_iterator it =
            rates.upper_bound(date);

    if (it == rates.begin())
    {
        std::cerr << "Error: no earlier date available => "
                  << date << std::endl;
        continue;
    }

    --it;

    std::cout << date << " => " << value << " = " << value * it->second << std::endl;
  }
}
