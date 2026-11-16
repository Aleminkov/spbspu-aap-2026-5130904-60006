#include <iostream>
#include <limits>

int main()
{
  int current_value = 0;
  int previous_value = 0;
  int last_non_zero = 0;

  int value_count = 0;
  int current_run_length = 0;
  int max_run_length = 0;
  int sign_changes = 0;

  while (true) {
    if (!(std::cin >> current_value)) {
      std::cerr << "Error: Invalid input data or missing zero terminator." << std::endl;
      return 1;
    }

    if (current_value == 0) {
      break;
    }

    if (value_count == std::numeric_limits< int >::max()) {
      std::cerr << "Error: Input sequence is too long." << std::endl;
      return 2;
    }
    ++value_count;

    if (current_value >= previous_value) {
      if (current_run_length == std::numeric_limits< int >::max()) {
        std::cerr << "Error: Increasing fragment is too long." << std::endl;
        return 2;
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
        return 2;
      }
      ++sign_changes;
    }

    previous_value = current_value;
    last_non_zero = current_value;
  }

  std::cout << max_run_length << std::endl;
  std::cout << sign_changes << std::endl;

  return 0;
}
