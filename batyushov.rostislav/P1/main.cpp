#include <cctype>
#include <iostream>
#include <limits>

namespace batyushov
{
  const int inputError = 1;
  const int shortError = 2;
  const int overflowError = 2;

  int run()
  {
    int number = 0;
    int prev = 0;
    int prev_prev = 0;
    int count = 0;

    long long cur_dec = 0;
    long long max_dec = 0;
    long long loc_max = 0;

    bool dec_overflow = false;
    bool loc_max_overflow = false;

    const long long max_ll = std::numeric_limits< long long >::max();

    while (std::cin >> number && number != 0)
    {
      if (count > 0 && number <= prev)
      {
        if (cur_dec == max_ll)
        {
          dec_overflow = true;
        }
        else
        {
          cur_dec++;
        }
      }
      else
      {
        cur_dec = 1;
      }
      if (cur_dec > max_dec)
      {
        max_dec = cur_dec;
      }

      if (count >= 2 && prev > prev_prev && prev > number)
      {
        if (loc_max == max_ll)
        {
          loc_max_overflow = true;
        }
        else
        {
          loc_max++;
        }
      }

      prev_prev = prev;
      prev = number;
      if (count < 2)
      {
        count++;
      }
    }

    if (!std::cin || (!std::cin.eof() && !std::isspace(std::cin.peek())))
    {
      std::cerr << "Ошибка: ввод не является последовательностью целых чисел\n";
      return batyushov::inputError;
    }

    if (dec_overflow)
    {
      std::cerr << "Ошибка: переполнение счётчика убывающей подпоследовательности\n";
    }
    else
    {
      std::cout << max_dec << '\n';
    }

    if (count == 0)
    {
      std::cerr << "Ошибка: последовательность слишком короткая\n";
      return batyushov::shortError;
    }

    if (loc_max_overflow)
    {
      std::cerr << "Ошибка: переполнение счётчика локальных максимумов\n";
    }
    else
    {
      std::cout << loc_max << '\n';
    }

    if (dec_overflow || loc_max_overflow)
    {
      return batyushov::overflowError;
    }
    return 0;
  }
}

int main()
{
  return batyushov::run();
}
