#include <iostream>
#include <limits>
namespace bondarenko {
  using ull = unsigned long long;
  const int INVALID_DATA = 1;
  const int INVALID_ARGUMENTS = 2;

  const ull ullmax = std::numeric_limits< ull >::max();

  void problemA(int &n, int &max, ull &a_count, bool &is_over_flow_a)
  {
    if (n > max) {
      max = n;
      a_count = 0;
    } else {
      if (a_count == ullmax) {
        is_over_flow_a = true;
        return;
      }
      a_count++;
    }
  }

  void problemB(ull &count, int &cur, int &n, ull &b_count, ull &b_max, bool &is_over_flow_b)
  {
    if (count == 0) {
      cur = n;
      b_count = b_max = 1;
    } else {
      if (n >= cur) {
        if (b_count == ullmax) {
          is_over_flow_b = true;
          return;
        }
        b_count++;
      } else {
        b_count = 1;
      }
      b_max = b_max < b_count ? b_count : b_max;
      cur = n;
    }
  }
}

int main()
{
  int max = std::numeric_limits< int >::min();

  bondarenko::ull count = 0, a_count = 0, b_count = 0, b_max = 0;
  int n = 0, cur = 0;
  bool is_over_flow_a = false, is_over_flow_b = false, is_over_flow = false;

  while (std::cin >> n) {
    if (n == 0) {
      break;
    }
    if (count == bondarenko::ullmax) {
      is_over_flow = true;
      break;
    }
    count++;

    bondarenko::problemB(count, cur, n, b_count, b_max, is_over_flow_b);

    bondarenko::problemA(n, max, a_count, is_over_flow_a);

    if (is_over_flow_a == true || is_over_flow_b == true) {
      break;
    }
  }

  if (std::cin.fail()) {
    std::cerr << "Expects error output (return code 1)\n";
    return bondarenko::INVALID_DATA;
  }

  if (is_over_flow || (is_over_flow_a && is_over_flow_b)) {
    std::cerr << "Expects error output (return code 2)\n";
    return bondarenko::INVALID_ARGUMENTS;
  }

  if (n == 0) {
    if (count == 0) {
      std::cout << a_count << "\n";
      std::cerr << "Expects error output (return code 2)\n";
      return bondarenko::INVALID_ARGUMENTS;
    }
    if (is_over_flow_a) {
      std::cout << b_max << "\n";
      std::cerr << "Expects error output (return code 2)\n";
      return bondarenko::INVALID_ARGUMENTS;
    }
    if (is_over_flow_b) {
      std::cout << a_count << "\n";
      std::cerr << "Expects error output (return code 2)\n";
      return bondarenko::INVALID_ARGUMENTS;
    }
    std::cout << a_count << "\n";
    std::cout << b_max << "\n";
    return 0;
  }
}
