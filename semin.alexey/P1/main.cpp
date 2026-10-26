#include <iostream>

int main()
{
  int number = 0;
  int previous = 0;

  int count_dec = 0;
  int max_dec = 0;

  int count_even = 0;
  int max_even = 0;

  while (true)
  {
    if (!(std::cin >> number))
    {
      std::cerr << "Ошибка ввода" << '\n';
      return 1;
    }

    if (number == 0)
    {
      break;
    }

    if (count_dec == 0 || number > previous)
    {
      count_dec = 1;
    }
    else
    {
      count_dec++;
    }

    if (count_dec > max_dec)
    {
      max_dec = count_dec;
    }

    if (number % 2 == 0)
    {
      count_even++;

      if (count_even > max_even)
      {
        max_even = count_even;
      }
    }
    else
    {
      count_even = 0;
    }

    previous = number;
  }

  std::cout << max_dec << '\n';
  std::cout << max_even << '\n';

  return 0;
}
