#include <iostream>
#include <limits>
#include <cstddef>

namespace dortman
{
  const int not_a_sequence = 1;
  const int invalid_data = 2;
}

int main()
{
  int value = 0;
  bool has_elements = false;

  int max_val = 0;
  size_t max_count = 0;
  bool overflow_max_count = false;

  size_t current_even = 0;
  size_t max_even = 0;
  bool overflow_even = false;

  const size_t max_limit = std::numeric_limits< size_t >::max();

  while (std::cin >> value && value != 0)
  {
    if (!has_elements || value > max_val)
    {
      max_val = value;
      max_count = 1;
      overflow_max_count = false;
    }
    else if (value == max_val)
    {
      if (max_count == max_limit)
      {
        overflow_max_count = true;
      }
      else
      {
        ++max_count;
      }
    }

    if ((value & 1) == 0)
    {
      if (current_even == max_limit)
      {
        overflow_even = true;
      }
      else
      {
        ++current_even;
        if (current_even > max_even)
        {
          max_even = current_even;
        }
      }
    }
    else
    {
      current_even = 0;
    }

    has_elements = true;
  }

  if (!std::cin)
  {
    std::cerr << "Не является последовательностью\n";
    return dortman::not_a_sequence;
  }

  bool has_error = false;

  if (overflow_even)
  {
    has_error = true;
    std::cerr << "Переполнение счетчика четных элементов\n";
  }
  else
  {
    std::cout << max_even << "\n";
  }

  if (!has_elements)
  {
    has_error = true;
    std::cerr << "Последовательность слишком короткая\n";
  }
  else if (overflow_max_count)
  {
    has_error = true;
    std::cerr << "Переполнение счетчика максимальных элементов\n";
  }
  else
  {
    std::cout << max_count << "\n";
  }

  if (has_error)
  {
    return dortman::invalid_data;
  }

  return 0;
}
