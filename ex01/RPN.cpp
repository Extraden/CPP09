#include "RPN.hpp"
#include <sstream>
#include <stack>

static int calculate(int left, int right, char c)
{
  int result = 0;

  if (c == '+')
    result = left + right;
  else if (c == '-')
    result = left - right;
  else if (c == '*')
    result = left * right;
  else if (c == '/')
    result = left / right;
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

        int right = s.top();
        s.pop();
        int left = s.top();
        int tmp_res = calculate(left, right, c);
        s.top() = tmp_res;
      }
    else 
      throw std::runtime_error("Error");
  }
  return s.top();
}
