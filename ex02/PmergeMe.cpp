#include "PmergeMe.hpp"
#include <vector>
#include <cerrno>
#include <climits>
#include <cstdlib>
#include <sstream>
#include <stdexcept>

void  parseArguments(int argc, char *argv[], std::vector<int>& v)
{
  int i = 1;

  while (i < argc)
  {
    std::istringstream iss(argv[i]);
    std::string token;

    while (iss >> token)
    {
      errno = 0;
      char *end;

      long value = std::strtol(token.c_str(), &end, 10);

      if (token.c_str() == end || *end != '\0' || value <= 0 || value > INT_MAX
          || errno == ERANGE)
        throw std::runtime_error("Error");
      v.push_back(value);
    }
    i++;
  }
}

