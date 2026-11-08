#include <iostream>
#include <limits>

const int exit_success = 0;
const int exit_invalid_input = 1;
const int exit_calc_error = 2;

using Counter = unsigned long long;

bool safeIncrement(Counter& counter)
{
  if (counter == std::numeric_limits< Counter >::max()) {
    return false;
  }
  ++counter;
  return true;
}

Counter absValue(int value)
{
  const Counter v = static_cast< Counter >(value);
  return value < 0 ? 0ULL - v : v;
}

int main()
{
  int previous2 = 0;
  int previous1 = 0;
  int current = 0;
  int elements = 0;

  Counter count_grt = 0;
  Counter count_pth = 0;
  bool grt_overflow = false;
  bool pth_overflow = false;
  bool after_zero = false;

  while (std::cin >> current) {
    if (after_zero) {
      continue;
    }

    if (current == 0) {
      after_zero = true;
      continue;
    }

    if (elements >= 2) {
      if (previous1 < previous2 && previous1 > current) {
        if (!safeIncrement(count_grt)) {
          grt_overflow = true;
        }
      }

      const Counter a = absValue(previous2);
      const Counter b = absValue(previous1);
      const Counter c = absValue(current);
      if (a * a + b * b == c * c) {
        if (!safeIncrement(count_pth)) {
          pth_overflow = true;
        }
      }
    }

    previous2 = previous1;
    previous1 = current;
    if (elements < 2) {
      ++elements;
    }
  }

  if (!after_zero) {
    if (std::cin.eof()) {
      std::cerr << "Error: missing terminating zero\n";
    } else {
      std::cerr << "Error: invalid input\n";
    }
    return exit_invalid_input;
  }

  if (!std::cin.eof()) {
    std::cerr << "Error: invalid input after zero\n";
    return exit_invalid_input;
  }

  if (!grt_overflow) {
    std::cout << count_grt << '\n';
  } else {
    std::cerr << "Error: counter overflow (GRT-LSS)\n";
  }

  if (!pth_overflow) {
    std::cout << count_pth << '\n';
  } else {
    std::cerr << "Error: counter overflow (PTH-TRP)\n";
  }

  return (grt_overflow || pth_overflow) ? exit_calc_error : exit_success;
}
