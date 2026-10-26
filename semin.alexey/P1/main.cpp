#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>

constexpr unsigned long long k_max_fixed_elements = 10000;

bool equals(const char* left, const char* right)
{
  while (*left != '\0' && *right != '\0' && *left == *right) {
    ++left;
    ++right;
  }
  return *left == *right;
}

unsigned long long read_dimension(std::istream& input)
{
  char token[32] = {};
  input.width(32);
  if (!(input >> token)) {
    if (input.bad()) {
      throw std::runtime_error("Failed to read input file");
    }
    throw std::invalid_argument("Missing or invalid matrix dimension");
  }

  unsigned long long value = 0;
  for (int i = 0; token[i] != '\0'; ++i) {
    if (i >= 20) {
      throw std::overflow_error("Matrix dimension is too large");
    }
    if (token[i] < '0' || token[i] > '9') {
      throw std::invalid_argument("Matrix dimensions must be non-negative integers");
    }
    const unsigned long long digit =
        static_cast<unsigned long long>(token[i] - '0');
    if (value > (std::numeric_limits<unsigned long long>::max() - digit) / 10) {
      throw std::overflow_error("Matrix dimension is too large");
    }
    value = value * 10 + digit;
  }
  return value;
}

void read_matrix_header(
    std::istream& input,
    unsigned long long& rows,
    unsigned long long& cols,
    unsigned long long& element_count)
{
  rows = read_dimension(input);
  cols = read_dimension(input);

  if ((rows == 0) != (cols == 0)) {
    throw std::invalid_argument(
        "A matrix must have either two positive dimensions or be 0 by 0");
  }
  if (rows == 0) {
    element_count = 0;
    return;
  }

  if (cols > std::numeric_limits<unsigned long long>::max() / rows) {
    throw std::overflow_error("Matrix element count is too large");
  }
  element_count = rows * cols;
  if (element_count >
      std::numeric_limits<unsigned long long>::max() / sizeof(long long)) {
    throw std::overflow_error("Matrix storage size is too large");
  }
}

void read_matrix_elements(
    std::istream& input,
    unsigned long long element_count,
    long long* matrix)
{
  for (unsigned long long i = 0; i < element_count; ++i) {
    int value = 0;
    if (!(input >> value)) {
      if (input.bad()) {
        throw std::runtime_error("Failed to read input file");
      }
      throw std::invalid_argument("Invalid or incomplete matrix data");
    }
    matrix[i] = value;
  }

  char extra[2] = {};
  input.width(2);
  if (input >> extra) {
    throw std::invalid_argument("Unexpected data after the matrix");
  }
  if (input.bad()) {
    throw std::runtime_error("Failed to read input file");
  }
}

void decrease_clockwise_from_top_left(
    long long* matrix,
    unsigned long long rows,
    unsigned long long cols)
{
  unsigned long long top = 0;
  unsigned long long bottom = rows;
  unsigned long long left = 0;
  unsigned long long right = cols;
  long long decrement = 1;

  const auto decrease = [&](unsigned long long row, unsigned long long col)
  {
    matrix[row * cols + col] -= decrement;
    ++decrement;
  };

  while (top < bottom && left < right) {
    for (unsigned long long col = left; col < right; ++col) {
      decrease(top, col);
    }
    ++top;
    if (top >= bottom) {
      break;
    }

    --right;
    for (unsigned long long row = top; row < bottom; ++row) {
      decrease(row, right);
    }
    if (left >= right) {
      break;
    }

    --bottom;
    for (unsigned long long col = right; col > left; --col) {
      decrease(bottom, col - 1);
    }

    ++left;
    for (unsigned long long row = bottom; row > top; --row) {
      decrease(row - 1, left - 1);
    }
  }
}

void write_matrix(
    std::ostream& output,
    const long long* matrix,
    unsigned long long rows,
    unsigned long long cols)
{
  output << rows << ' ' << cols;
  for (unsigned long long i = 0; i < rows * cols; ++i) {
    output << ' ' << matrix[i];
  }
  output << '\n';
  if (!output) {
    throw std::runtime_error("Failed to write output file");
  }
}

int process_matrix(
    std::ostream& output,
    long long* matrix,
    unsigned long long rows,
    unsigned long long cols)
{
  decrease_clockwise_from_top_left(matrix, rows, cols);
  write_matrix(output, matrix, rows, cols);
  return 0;
}

int run_fixed_storage(std::istream& input, std::ostream& output)
{
  long long fixed_matrix[k_max_fixed_elements] = {};
  unsigned long long rows = 0;
  unsigned long long cols = 0;
  unsigned long long element_count = 0;

  read_matrix_header(input, rows, cols, element_count);
  if (element_count > k_max_fixed_elements) {
    throw std::length_error(
        "Matrix exceeds the 10000 element fixed-storage limit");
  }
  read_matrix_elements(input, element_count, fixed_matrix);
  return process_matrix(output, fixed_matrix, rows, cols);
}

int run_dynamic_storage(std::istream& input, std::ostream& output)
{
  unsigned long long rows = 0;
  unsigned long long cols = 0;
  unsigned long long element_count = 0;
  read_matrix_header(input, rows, cols, element_count);

  long long* dynamic_matrix = nullptr;
  try {
    if (element_count != 0) {
      dynamic_matrix = new long long[element_count];
    }
    read_matrix_elements(input, element_count, dynamic_matrix);
    const int result =
        process_matrix(output, dynamic_matrix, rows, cols);
    delete[] dynamic_matrix;
    return result;
  } catch (...) {
    delete[] dynamic_matrix;
    throw;
  }
}

int run_matrix_program(int argc, char** argv)
{
  if (argc != 4) {
    throw std::invalid_argument("Invalid number of arguments");
  }

  if (!equals(argv[1], "1") && !equals(argv[1], "2")) {
    throw std::invalid_argument("First parameter must be 1 or 2");
  }

  std::ifstream input(argv[2]);
  if (!input) {
    throw std::runtime_error("Cannot open input file");
  }

  std::ofstream output(argv[3]);
  if (!output) {
    throw std::runtime_error("Cannot open output file");
  }

  try {
    if (equals(argv[1], "1")) {
      return run_fixed_storage(input, output);
    }
    return run_dynamic_storage(input, output);
  } catch (const std::overflow_error& error) {
    std::cerr << error.what() << '\n';
    return 2;
  } catch (const std::runtime_error&) {
    throw;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 2;
  }
}

int run_intro()
{
  std::cout << "semin.alexey\n";
  if (!std::cout) {
    throw std::runtime_error("Failed to write output");
  }
  return 0;
}

int run_sequence()
{
  int previous = 0;
  int current = 0;
  int increasing_pairs = 0;
  bool has_previous = false;
  bool has_terminator = false;

  while (std::cin >> current) {
    if (current == 0) {
      has_terminator = true;
      break;
    }

    if (has_previous && current > previous) {
      ++increasing_pairs;
    }
    previous = current;
    has_previous = true;
  }

  if (std::cin.bad()) {
    throw std::runtime_error("Failed to read standard input");
  }
  if (!has_terminator) {
    throw std::invalid_argument("Expected integers terminated by 0");
  }

  std::cout << increasing_pairs << '\n';
  if (!std::cout) {
    throw std::runtime_error("Failed to write output");
  }
  return 0;
}

int main(int argc, char** argv)
{
  try {
    if (argc == 1) {
      return run_intro();
    }
    if (argc == 2 && equals(argv[1], "sequence")) {
      return run_sequence();
    }
    return run_matrix_program(argc, argv);
  } catch (const std::invalid_argument& error) {
    std::cerr << error.what() << '\n';
    return 1;
  } catch (const std::overflow_error& error) {
    std::cerr << error.what() << '\n';
    return 1;
  } catch (const std::runtime_error& error) {
    std::cerr << error.what() << '\n';
    return 1;
  } catch (const std::exception& error) {
    std::cerr << error.what() << '\n';
    return 1;
  }
}
