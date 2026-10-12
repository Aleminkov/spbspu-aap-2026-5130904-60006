#include <iostream>

int main()
{
  int before_previous = 0;
  int previous = 0;
  int count = 0;
  int found = 0;
  int x = 0;
  const int inputError = 1;
  const int minReadBeforeTriple = 2;
  int current_length = 0;
  int best_length = 0;
  while (std::cin >> x && x != 0) {
    if (count >= minReadBeforeTriple && before_previous > previous && previous > x) {
      ++found;
    }
    if (count > 0 && x >= previous) {
      ++current_length;
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
  std::cout << best_length << "\n" << found << "\n";
  return 0;
}
