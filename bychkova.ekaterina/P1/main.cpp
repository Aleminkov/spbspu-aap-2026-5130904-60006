#include <iostream>
#include <limits>

namespace bychkova {
  constexpr int inputErrorCode = 1;
  constexpr int errorSum = 2;
}

int main()
{
  int current_value = 0;
  int previous_value = 0;
  int last_non_zero = 0;

  int value_count = 0;
  int current_run_length = 0;
  int max_run_length = 0;
  int sign_changes = 0;

  while (std::cin >> current_value && current_value != 0) {
    if (value_count == std::numeric_limits< int >::max()) {
      std::cerr << "Error: Input sequence is too long." << std::endl;
      return bychkova::errorSum;
    }
    ++value_count;

    if (current_value >= previous_value) {
      if (current_run_length == std::numeric_limits< int >::max()) {
        std::cerr << "Error: Increasing fragment is too long." << std::endl;
        return bychkova::errorSum;
      }
      ++current_run_length;
    } else {
      current_run_length = 1;
    }

    if (current_run_length > max_run_length) {
      max_run_length = current_run_length;
    }

    if (last_non_zero != 0 && ((last_non_zero < 0 && current_value > 0) || (last_non_zero > 0 && current_value < 0))) {
      if (sign_changes == std::numeric_limits< int >::max()) {
        std::cerr << "Error: Too many sign changes." << std::endl;
        return bychkova::errorSum;
      }
      ++sign_changes;
    }

    previous_value = current_value;
    last_non_zero = current_value;
  }

  if (!std::cin) {
    std::cerr << "Error: Invalid input data or missing zero terminator." << std::endl;
    return bychkova::inputErrorCode;
  }

  std::cout << max_run_length << std::endl;
  std::cout << sign_changes << std::endl;

  return 0;
}
