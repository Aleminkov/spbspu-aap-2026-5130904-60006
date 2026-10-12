#include <iostream>

int main()
{
  int beforePrevious = 0;
  int previous = 0;
  int count = 0;
  int found = 0;
  int x = 0;
  const int inputError = 1;
  const int minReadBeforeTriple = 2;
  int currentLength = 0;
  int bestLength = 0;
  while (std::cin >> x && x != 0) {
    if (count >= minReadBeforeTriple && beforePrevious > previous && previous > x) {
      ++found;
    }
    if (count > 0 && x >= previous) {
      ++currentLength;
    } else {
      currentLength = 1;
    }
    if (currentLength > bestLength) {
      bestLength = currentLength;
    }
    beforePrevious = previous;
    previous = x;
    ++count;
  }
  if (std::cin.fail()) {
    std::cerr << "Error: invalid input\n";
    return inputError;
  }
  std::cout << bestLength << "\n" << found << "\n";
  return 0;
}
