#include <iostream>
#include <limits>

int main()
{
  int before_previous = 0;
  int previous = 0;
  int count = 0;
  int found = 0;
  int x = 0;
  const int inputError = 1;
  const int overflowError = 2;
  const int minReadBeforeTriple = 2;
  int current_length = 0;
  int best_length = 0;
  bool found_overflow = false;
  bool length_overflow = false;
  while (std::cin >> x && x != 0) {
    if (count >= minReadBeforeTriple && before_previous > previous && previous > x) {
      if (found == std::numeric_limits<int>::max()) {
        found_overflow = true;
      } else {
        ++found;
      }
    }
    if (count > 0 && x >= previous) {
      if (current_length == std::numeric_limits<int>::max()) {
        length_overflow = true;
      } else {
        ++current_length;
      }
    } else {
      current_length = 1;
    }
    if (current_length > best_length) {
      best_length = current_length;
    }
    before_previous = previous;
    previous = x;
    ++count;
  }
  if (std::cin.fail()) {
    std::cerr << "Error: invalid input\n";
    return inputError;
  }
  if (!length_overflow) {
    std::cout << best_length << "\n";
  }
  if (!found_overflow) {
    std::cout << found << "\n";
  }
  if (length_overflow) {
    std::cerr << "Error: length overflow\n";
  }
  if (found_overflow) {
    std::cerr << "Error: found overflow\n";
  }
  if (length_overflow || found_overflow) {
    return overflowError;
  }
  return 0;
}
