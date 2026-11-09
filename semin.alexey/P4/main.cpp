#include <cctype>
#include <cstddef>
#include <iostream>
#include <limits>

void removeVowels(char* text) noexcept
{
  std::size_t source_index = 0;
  std::size_t target_index = 0;
  while (text[source_index] != '\0') {
    const unsigned char character = static_cast< unsigned char >(text[source_index]);
    const int lowercase = std::tolower(character);
    if (lowercase != 'a' && lowercase != 'e' && lowercase != 'i' && lowercase != 'o' && lowercase != 'u') {
      text[target_index] = text[source_index];
      ++target_index;
    }
    ++source_index;
  }
  text[target_index] = '\0';
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
  bool has_input = false;
  while (std::cin.get(character)) {
    has_input = true;
    if (character == '\n') {
      break;
    }
    if (length >= capacity - 1) {
      if (capacity > std::numeric_limits< std::size_t >::max() / 2) {
        delete[] text;
        std::cerr << "memory allocation error\n";
        return 1;
      }
      const std::size_t new_capacity = capacity * 2;
      char* new_text = nullptr;
      try {
        new_text = new char[new_capacity];
      } catch (...) {
        delete[] text;
        std::cerr << "memory allocation error\n";
        return 1;
      }
      for (std::size_t index = 0; index < length; ++index) {
        new_text[index] = text[index];
      }
      delete[] text;
      text = new_text;
      capacity = new_capacity;
    }
    text[length] = character;
    ++length;
  }

  if (std::cin.bad() || (!std::cin.eof() && std::cin.fail())) {
    delete[] text;
    std::cerr << "input error\n";
    return 1;
  }
  if (!has_input) {
    delete[] text;
    std::cerr << "no input\n";
    return 1;
  }

  text[length] = '\0';
  removeVowels(text);
  std::cout << text << '\n';
  delete[] text;
  return 0;
}
