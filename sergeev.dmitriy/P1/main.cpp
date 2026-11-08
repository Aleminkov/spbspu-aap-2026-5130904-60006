#include <iostream>
#include <limits>

int main()
{
  int const ERROR_INVALID_INPUT = 1;
  int const ERROR_CALCULATION = 2;

  int min = 0;
  int current = 0, previous = 0, next = 0;
  int count_10 = 0, count_16 = 1;

  bool is_overflow_10 = false;
  bool is_overflow_16 = false;

  if (!(std::cin >> previous))
  {
    std::cerr << "error import\n";
    return ERROR_INVALID_INPUT;
  }

  min = previous;

  if (previous == 0)
  {
    std::cout << "0" << "\n";
    std::cout << "0" << "\n";
    return 0;
  }

  if (!(std::cin >> current))
  {
    std::cerr << "error import\n";
    return ERROR_INVALID_INPUT;
  }

  if (current == 0)
  {
    std::cout << count_10 << "\n";
    std::cout << count_16 << "\n";
    return 0;
  }

  if (current < previous)
  {
    min = current;
  }
  else if (current == min)
  {
    if (count_16 > std::numeric_limits< int >::max() - 1)
    {
      is_overflow_16 = true;
    }
    else
    {
      count_16++;
    }
  }

  while (std::cin >> next)
  {
    if (next == 0)
    {
      break;
    }

    if (current < previous && current > next)
    {
      if (count_10 > std::numeric_limits< int >::max() - 1)
      {
        is_overflow_10 = true;
      }
      else
      {
        count_10++;
      }
    }

    if (next < min)
    {
      min = next;
      count_16 = 1;
    }
    else if (next == min)
    {
      if (count_16 > std::numeric_limits< int >::max() - 1)
      {
        is_overflow_16 = true;
      }
      else
      {
        count_16++;
      }
    }

    previous = current;
    current = next;
  }

  if (std::cin.fail())
  {
    std::cerr << "error import\n";
    return ERROR_INVALID_INPUT;
  }

  if (is_overflow_10)
  {
    std::cerr << "error calculation 10\n";
  }
  else
  {
    std::cout << count_10 << "\n";
  }

  if (is_overflow_16)
  {
    std::cerr << "error calculation 16\n";
  }
  else
  {
    std::cout << count_16 << "\n";
  }

  if (is_overflow_10 || is_overflow_16)
  {
    return ERROR_CALCULATION;
  }
  return 0;
}
