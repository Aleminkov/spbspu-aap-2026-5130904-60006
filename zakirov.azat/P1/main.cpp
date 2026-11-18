#include <iostream>
#include <limits>
#include <cstddef>

namespace zakirov
{
  const int input_error = 1;
  const int calculation_error = 2;
}

int main()
{
  int number = 0;
  int last = 0;
  int smallest = 0;

  std::size_t minimums = 0;
  std::size_t divs = 0;

  bool first = true;
  bool enough_numbers = false;
  bool minimum_error = false;
  bool div_error = false;

  const std::size_t limit = std::numeric_limits< std::size_t >::max();

  while (std::cin >> number)
  {
    if (number == 0)
    {
      break;
    }

    if (first)
    {
      smallest = number;
      minimums = 1;
      last = number;
      first = false;
      continue;
    }

    enough_numbers = true;

    if (number < smallest)
    {
      smallest = number;
      minimums = 1;
      minimum_error = false;
    }
    else if (number == smallest)
    {
      if (minimums < limit)
      {
        minimums++;
      }
      else
      {
        minimum_error = true;
      }
    }

    if (last == -1 || number % last == 0)
    {
      if (divs < limit)
      {
        divs++;
      }
      else
      {
        div_error = true;
      }
    }

    last = number;
  }

  if (!std::cin)
  {
    std::cerr << "Ошибка ввода\n";
    return zakirov::input_error;
  }

  if (!minimum_error)
  {
    std::cout << minimums << '\n';
  }
  else
  {
    std::cerr << "16: переполнение\n";
  }

  if (!enough_numbers)
  {
    std::cerr << "11: мало чисел\n";
  }
  else if (div_error)
  {
    std::cerr << "11: переполнение\n";
  }
  else
  {
    std::cout << divs << '\n';
  }

  if (minimum_error || div_error || !enough_numbers)
  {
    return zakirov::calculation_error;
  }

  return 0;
}
