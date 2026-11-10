#include <iostream>
#include <limits>
#include <cstddef>

namespace proskuryakov
{
  const int err_invalid_data = 1;
  const int err_sequence_small = 2;
}

int main()
{
  int value = 0;
  size_t total_count = 0;
  size_t count_max = 0;
  size_t count_min = 0;
  bool overflow_max = false;
  bool overflow_min = false;
  int max = 0;
  int min = 0;
  while (std::cin >> value)
  {
    if (value == 0)
    {
      break;
    }
    if (total_count < 2)
    {
      total_count += 1;
    }

    if (total_count == 1 || value > max)
    {
      max = value;
      count_max = 1;
      overflow_max = false;
    }
    else if (value == max)
    {
      if (count_max == std::numeric_limits< size_t >::max())
      {
        overflow_max = true;
      }
      count_max += 1;
    }

    if (total_count == 1 || value < min)
    {
      min = value;
      count_min = 1;
      overflow_min = false;
    }
    else if (value == min)
    {
      if (count_min == std::numeric_limits< size_t >::max())
      {
        overflow_min = true;
      }
      count_min += 1;
    }
  }

  if (!std::cin)
  {
    std::cerr << "Invalid input!\n";
    return proskuryakov::err_invalid_data;
  }

  if (total_count == 0)
  {
    std::cerr << "Sequence is small!\n";
    return proskuryakov::err_sequence_small;
  }

  int result = 0;

  if (overflow_max)
  {
    std::cerr << "Overflow error!\n";
    result = proskuryakov::err_invalid_data;
  }
  else
  {
    std::cout << count_max << '\n';
  }

  if (overflow_min)
  {
    std::cerr << "Overflow error!\n";
    result = proskuryakov::err_invalid_data;
  }
  else
  {
    std::cout << count_min << '\n';
  }

  return result;
}
