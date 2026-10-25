#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>

using namespace std;

constexpr unsigned long long kMaxFixedElements = 10000;

bool equals(const char* left, const char* right)
{
  while (*left != '\0' && *right != '\0' && *left == *right) {
    ++left;
    ++right;
  }
  return *left == *right;
}

unsigned long long readDimension(istream& input)
{
  char token[32] = {};
  input.width(32);
  if (!(input >> token)) {
    if (input.bad()) {
      throw runtime_error("Failed to read input file");
    }
    throw invalid_argument("Missing or invalid matrix dimension");
  }

  unsigned long long value = 0;
  for (int i = 0; token[i] != '\0'; ++i) {
    if (i >= 20) {
      throw overflow_error("Matrix dimension is too large");
    }
    if (token[i] < '0' || token[i] > '9') {
      throw invalid_argument("Matrix dimensions must be non-negative integers");
    }
    const unsigned long long digit = static_cast< unsigned long long >(token[i] - '0');
    if (value > (numeric_limits< unsigned long long >::max() - digit) / 10) {
      throw overflow_error("Matrix dimension is too large");
    }
    value = value * 10 + digit;
  }
  return value;
}

void readMatrixHeader(
    istream& input, unsigned long long& rows, unsigned long long& cols, unsigned long long& elementCount)
{
  rows = readDimension(input);
  cols = readDimension(input);

  if ((rows == 0) != (cols == 0)) {
    throw invalid_argument("A matrix must have either two positive dimensions or be 0 by 0");
  }
  if (rows == 0) {
    elementCount = 0;
    return;
  }

  if (cols > numeric_limits< unsigned long long >::max() / rows) {
    throw overflow_error("Matrix element count is too large");
  }
  elementCount = rows * cols;
  if (elementCount > numeric_limits< unsigned long long >::max() / sizeof(long long)) {
    throw overflow_error("Matrix storage size is too large");
  }
}

void readMatrixElements(istream& input, unsigned long long elementCount, long long* matrix)
{
  for (unsigned long long i = 0; i < elementCount; ++i) {
    int value = 0;
    if (!(input >> value)) {
      if (input.bad()) {
        throw runtime_error("Failed to read input file");
      }
      throw invalid_argument("Invalid or incomplete matrix data");
    }
    matrix[i] = value;
  }

  char extra[2] = {};
  input.width(2);
  if (input >> extra) {
    throw invalid_argument("Unexpected data after the matrix");
  }
  if (input.bad()) {
    throw runtime_error("Failed to read input file");
  }
}

void decreaseClockwiseFromTopLeft(long long* matrix, unsigned long long rows, unsigned long long cols)
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

void writeMatrix(ostream& output, const long long* matrix, unsigned long long rows, unsigned long long cols)
{
  output << rows << ' ' << cols;
  for (unsigned long long i = 0; i < rows * cols; ++i) {
    output << ' ' << matrix[i];
  }
  output << '\n';
  if (!output) {
    throw runtime_error("Failed to write output file");
  }
}

int processMatrix(ostream& output, long long* matrix, unsigned long long rows, unsigned long long cols)
{
  decreaseClockwiseFromTopLeft(matrix, rows, cols);
  writeMatrix(output, matrix, rows, cols);
  return 0;
}

int runFixedStorage(istream& input, ostream& output)
{
  long long fixedMatrix[kMaxFixedElements] = {};
  unsigned long long rows = 0;
  unsigned long long cols = 0;
  unsigned long long elementCount = 0;

  readMatrixHeader(input, rows, cols, elementCount);
  if (elementCount > kMaxFixedElements) {
    throw length_error("Matrix exceeds the 10000 element fixed-storage limit");
  }
  readMatrixElements(input, elementCount, fixedMatrix);
  return processMatrix(output, fixedMatrix, rows, cols);
}

int runDynamicStorage(istream& input, ostream& output)
{
  unsigned long long rows = 0;
  unsigned long long cols = 0;
  unsigned long long elementCount = 0;
  readMatrixHeader(input, rows, cols, elementCount);

  long long* dynamicMatrix = 0;
  try {
    if (elementCount != 0) {
      dynamicMatrix = new long long[elementCount];
    }
    readMatrixElements(input, elementCount, dynamicMatrix);
    const int result = processMatrix(output, dynamicMatrix, rows, cols);
    delete[] dynamicMatrix;
    return result;
  } catch (...) {
    delete[] dynamicMatrix;
    throw;
  }
}

int runMatrixProgram(int argc, char** argv)
{
  if (argc != 4) {
    throw invalid_argument("Invalid number of arguments");
  }

  if (!equals(argv[1], "1") && !equals(argv[1], "2")) {
    throw invalid_argument("First parameter must be 1 or 2");
  }

  ifstream input(argv[2]);
  if (!input) {
    throw runtime_error("Cannot open input file");
  }

  ofstream output(argv[3]);
  if (!output) {
    throw runtime_error("Cannot open output file");
  }

  try {
    if (equals(argv[1], "1")) {
      return runFixedStorage(input, output);
    }
    return runDynamicStorage(input, output);
  } catch (const overflow_error& error) {
    cerr << error.what() << '\n';
    return 2;
  } catch (const runtime_error&) {
    throw;
  } catch (const exception& error) {
    cerr << error.what() << '\n';
    return 2;
  }
}

int runIntro()
{
  cout << "semin.alexey\n";
  if (!cout) {
    throw runtime_error("Failed to write output");
  }
  return 0;
}

int runSequence()
{
  int previous = 0;
  int current = 0;
  int increasingPairs = 0;
  bool hasPrevious = false;
  bool hasTerminator = false;

  while (cin >> current) {
    if (current == 0) {
      hasTerminator = true;
      break;
    }

    if (hasPrevious && current > previous) {
      ++increasingPairs;
    }
    previous = current;
    hasPrevious = true;
  }

  if (cin.bad()) {
    throw runtime_error("Failed to read standard input");
  }
  if (!hasTerminator) {
    throw invalid_argument("Expected integers terminated by 0");
  }

  cout << increasingPairs << '\n';
  if (!cout) {
    throw runtime_error("Failed to write output");
  }
  return 0;
}

int main(int argc, char** argv)
{
  try {
    if (argc == 1) {
      return runIntro();
    }
    if (argc == 2 && equals(argv[1], "sequence")) {
      return runSequence();
    }
    return runMatrixProgram(argc, argv);
  } catch (const invalid_argument& error) {
    cerr << error.what() << '\n';
    return 1;
  } catch (const overflow_error& error) {
    cerr << error.what() << '\n';
    return 1;
  } catch (const runtime_error& error) {
    cerr << error.what() << '\n';
    return 1;
  } catch (const exception& error) {
    cerr << error.what() << '\n';
    return 1;
  }
}

