#include <iostream>
#include <cstddef>
#include <limits>

int main()
{
  const int ERR_INPUT = 1;
  const int ERR_PARTIAL = 2;
  const int ERR_OVERFLOW = 4;

  int x = 0;
  bool term = false;

  int maxv = 0;
  int secondmax = 0;
  bool hmax = false;
  bool hsecondmax = false;

  std::size_t count_loc_max = 0;
  int prev2 = 0;
  int prev1 = 0;
  std::size_t n = 0;

  while (std::cin >> x)
  {
    if (x == 0)
    {
      term = true;
      break;
    }

    if (!hmax)
    {
      maxv = x;
      hmax = true;
    }
    else if (x > maxv)
    {
      secondmax = maxv;
      hsecondmax = true;
      maxv = x;
    }
    else if (x == maxv)
    {
      secondmax = maxv;
      hsecondmax = true;
    }
    else if (!hsecondmax || x > secondmax)
    {
      secondmax = x;
      hsecondmax = true;
    }

    if (n >= 2 && prev1 > prev2 && prev1 > x)
    {
      if (count_loc_max == std::numeric_limits< std::size_t >::max())
      {
        std::cerr << "error: count_loc_max overflow\n";
        return ERR_OVERFLOW;
      }
      ++count_loc_max;
    }

    prev2 = prev1;
    prev1 = x;

    if (n == std::numeric_limits< std::size_t >::max())
    {
      std::cerr << "error: element counter overflow\n";
      return ERR_OVERFLOW;
    }
    ++n;
  }

  if (!term)
  {
    if (std::cin.eof())
    {
      std::cerr << "error: The sequence is not terminated with a zero\n";
    }
    else
    {
      std::cerr << "ошибка: The input data is not a sequence of integers\n";
    }
    return ERR_INPUT;
  }

  int retcode = 0;

  if (hsecondmax)
  {
    std::cout << "SUB-MAX: " << secondmax << '\n';
  }
  else
  {
    std::cerr << "error: cannot calculate SUB-MAX: sequence is too short\n";
    retcode = ERR_PARTIAL;
  }

  if (n > 0)
  {
    std::cout << "LOG-MAX: " << count_loc_max << '\n';
  }
  else
  {
    std::cerr << "error: cannot calculate LOG-MAX: sequence is too short\n";
    retcode = ERR_PARTIAL;
  }

  return retcode;
}
