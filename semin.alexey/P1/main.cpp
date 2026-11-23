#include <iostream>
#include <limits>
#include <stdexcept>

namespace semin
{
  void incrementCounter(size_t &counter)
  {
    if (counter == std::numeric_limits< size_t >::max()) {
      throw std::overflow_error("Переполнение счетчика");
    }

    ++counter;
  }
}

int main()
{
  constexpr int error_code = 1;

  int number = 0;
  int previous = 0;

  size_t count_dec = 0;
  int max_dec = 0;

  size_t count_even = 0;
  int max_even = 0;

  bool overflowed = false;
  bool dec_overflowed = false;
  bool even_overflowed = false;

  while (std::cin >> number) {
    if (number == 0) {
      break;
    }

    if (count_dec == 0 || number > previous) {
      count_dec = 1;
      dec_overflowed = false;
    } else if (!dec_overflowed) {
      try {
        semin::incrementCounter(count_dec);
      } catch (const std::overflow_error &) {
        overflowed = true;
        dec_overflowed = true;
      }
    }

    if (count_dec > max_dec) {
      max_dec = count_dec;
    }

    if (number % 2 == 0) {
      if (!even_overflowed) {
        try {
          semin::incrementCounter(count_even);
        } catch (const std::overflow_error &) {
          overflowed = true;
          even_overflowed = true;
        }
      }

      if (count_even > max_even) {
        max_even = count_even;
      }
    } else {
      count_even = 0;
      even_overflowed = false;
    }

    previous = number;
  }

  if (!std::cin) {
    std::cerr << "Ошибка ввода" << '\n';
    return error_code;
  }

  if (dec_overflowed) {
    std::cerr << "Переполнение счетчика" << '\n';
  } else {
    std::cout << max_dec << '\n';
  }

  if (even_overflowed) {
    std::cerr << "Переполнение счетчика" << '\n';
  } else {
    std::cout << max_even << '\n';
  }

  if (overflowed) {
    std::cerr << "Переполнение счетчика" << '\n';
    return error_code;
  }

  return 0;
}
