#include <iostream>
#include <limits>
#include <cstddef>

namespace haidov {
  const int correct_result = 0;
  const int invalid_input = 1;
  const int calculation_error = 2;

  int sequence()
  {
    int element = 0;
    size_t len_m_d = 0;
    size_t len_max = 0;
    int last_el = 0;
    int max = 0;
    bool len_max_too_long = false;
    bool len_m_d_too_long = false;
    while (std::cin >> element) {
      if (element == 0) {
        break;
      }
      if (last_el < element) {
        len_m_d = 0;
      }
      if (max < element) {
        len_max = 0;
        max = element;
      } else {
        if (len_max <= std::numeric_limits< size_t >::max() - 1) {
          len_max += 1;
        } else {
          len_max_too_long = true;
        }
      }
      last_el = element;
      if (len_m_d <= std::numeric_limits< size_t >::max() - 1) {
        len_m_d += 1;
      } else {
        len_m_d_too_long = true;
      }
    }
    if (std::cin.fail()) {
      std::cerr << "Wrong element in sequence" << std::endl;
    }
    int result = correct_result;
    if (len_m_d_too_long) {
      std::cerr << "Length of the biggest fragment is more than size_t limit" << std::endl;
      result = calculation_error;
    }
    std::cout << len_m_d << "\n";
    if (len_max_too_long) {
      std::cerr << "Amount of elements after maximal is more than size_t limit" << std::endl;
      result = calculation_error;
    }
    if (last_el == 0) {
      std::cerr << "Amount of elements after maximal uncounted" << std::endl;
      result = calculation_error;
    }
    std::cout << len_max << std::endl;
    return result;
  }
}

int main()
{
  haidov::sequence();
  return 0;
}
