#include <iostream>

int main()
{
  int number;
  int previous = 0;

  int countDec = 0;
  int maxDec = 0;

  int countEven = 0;
  int maxEven = 0;

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

    if (countDec == 0 || number > previous)
    {
      countDec = 1;
    }
    else
    {
      countDec++;
    }

    if (countDec > maxDec)
    {
      maxDec = countDec;
    }

    if (number % 2 == 0)
    {
      countEven++;

      if (countEven > maxEven)
      {
        maxEven = countEven;
      }
    }
    else
    {
      countEven = 0;
    }

    previous = number;
  }

  std::cout << maxDec << '\n';
  std::cout << maxEven << '\n';

  return 0;
}
