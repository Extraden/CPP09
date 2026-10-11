#include "RPN.hpp"
#include <climits>
#include <sstream>
#include <stack>
#include <stdexcept>

static long calculate(int left, int right, char c)
{
  long result = 0;

  if (c == '+')
    result = static_cast<long>(left) + right;
  else if (c == '-')
    result = static_cast<long>(left) - right;
  else if (c == '*')
    result = static_cast<long>(left) * right;
  else if (c == '/')
  {
    if (right == 0)
      throw std::runtime_error("Division by zero");
    result = static_cast<long>(left) / right;
  }
  else
    throw std::runtime_error("Error");

  return result;
}

int solve(const std::string& expr)
{
  std::stack<int> s;

  std::istringstream iss(expr);

  std::string token;
  char c;

  while (iss >> token)
  {
    if (token.size() != 1)  
      throw std::runtime_error("Error");

    c = token[0];
    if (c - '0' >= 0 && c - '0' <= 9)
      s.push(c - '0');
    else if (c == '+' || c == '-' || c == '*' || c == '/')
      {
        if (s.size() < 2)
          throw std::runtime_error("Error");
        int right = s.top();
        s.pop();
        int left = s.top();
        long tmp_res = calculate(left, right, c);
        if (tmp_res > INT_MAX || tmp_res < INT_MIN)
          throw std::runtime_error("Error");
        s.top() = tmp_res;
      }
    else 
      throw std::runtime_error("Error");
  }
  if (s.size() != 1)
    throw std::runtime_error("Error");
  return s.top();
}
