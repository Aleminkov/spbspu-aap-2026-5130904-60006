#include <iostream>
#include <limits>
#include <stdexcept>

using namespace std;

void incrementCounter(int & counter)
{
  if (counter == numeric_limits< int >::max()) {
    throw overflow_error("Переполнение счетчика");
  }

  ++counter;
}

int main()
{
  constexpr int error_code = 1;

  int number = 0;
  int previous = 0;

  int count_dec = 0;
  int max_dec = 0;

  int count_even = 0;
  int max_even = 0;

  try {
    while (cin >> number) {
      if (number == 0) {
        break;
      }

      if (count_dec == 0 || number > previous) {
        count_dec = 1;
      } else {
        incrementCounter(count_dec);
      }

      if (count_dec > max_dec) {
        max_dec = count_dec;
      }

      if (number % 2 == 0) {
        incrementCounter(count_even);

        if (count_even > max_even) {
          max_even = count_even;
        }
      } else {
        count_even = 0;
      }

      previous = number;
    }
  } catch (const overflow_error & error) {
    cerr << error.what() << '\n';
    return error_code;
  }

  if (!cin) {
    cerr << "Ошибка ввода" << '\n';
    return error_code;
  }

  cout << max_dec << '\n';
  cout << max_even << '\n';

  return 0;
}
