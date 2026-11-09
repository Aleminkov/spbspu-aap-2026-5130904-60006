#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>

void removeVowels(char* text) noexcept
{
  std::size_t sourceIndex = 0;
  std::size_t targetIndex = 0;
  while (text[sourceIndex] != '\0') {
    const unsigned char character =
      static_cast<unsigned char>(text[sourceIndex]);
    const int lowercase = std::tolower(character);
    if (lowercase != 'a' && lowercase != 'e' && lowercase != 'i' &&
        lowercase != 'o' && lowercase != 'u') {
      text[targetIndex] = text[sourceIndex];
      ++targetIndex;
    }
    ++sourceIndex;
  }
  text[targetIndex] = '\0';
}

int main()
{
  std::size_t capacity = 10;
  char* text = nullptr;
  try {
    text = new char[capacity];
  } catch (...) {
    std::cerr << "memory allocation error\n";
    return 1;
  }

  std::size_t length = 0;
  char character = '\0';
  while (std::cin.get(character) && character != '\n') {
    if (length >= capacity - 1) {
      if (capacity > std::numeric_limits<std::size_t>::max() / 2) {
        delete[] text;
        std::cerr << "memory allocation error\n";
        return 1;
      }
      const std::size_t newCapacity = capacity * 2;
      char* newText = nullptr;
      try {
        newText = new char[newCapacity];
      } catch (...) {
        delete[] text;
        std::cerr << "memory allocation error\n";
        return 1;
      }
      for (std::size_t index = 0; index < length; ++index) {
        newText[index] = text[index];
      }
      delete[] text;
      text = newText;
      capacity = newCapacity;
    }
    text[length] = character;
    ++length;
  }

  if (std::cin.bad() || (!std::cin.eof() && std::cin.fail())) {
    delete[] text;
    std::cerr << "input error\n";
    return 1;
  }

  text[length] = '\0';
  removeVowels(text);
  std::cout << text << '\n';
  delete[] text;
  return 0;
}