#include <iostream>
#include <limits>
#include <fstream>
#include <exception>


namespace segeev{
  int processVariant9(const int* matrix, size_t rows, size_t cols) {
    if (rows <= 1)
    {
      return cols;
    }

    size_t nonRepeatingColumnsCount = 0;

    for (size_t i = 0; i < cols; ++i) {
      bool hasDuplicates = false;
      for (size_t j = 0; j < rows - 1; ++j) {
        if (matrix[j * cols + i] == matrix[(j + 1) * cols + i]) {
          hasDuplicates = true;
          break;
        }
        }
      if (!hasDuplicates) {
        if (nonRepeatingColumnsCount > std::numeric_limits<size_t>::max() - 1){
          throw std::overflow_error("");
        }
        nonRepeatingColumnsCount++;
      }
    }
    return nonRepeatingColumnsCount;
  }
}



int main(int argc, char ** argv)
{
  const int SUCCESS = 0;
  const int ERROR_ARGS = 1;
  const int ERROR_DATA = 2;

  if (argc != 4) {
    std::cerr << "Error: Invalid number of arguments.\n" << std::endl;
    return ERROR_ARGS;
  }

  int num = 0;

  if (argv[1][0] == '1' && argv[1][1] == '\0') {
    num = 1;
  }
  else if(argv[1][0] == '2' && argv[1][1] == '\0') {
    num = 2;
  }
  else {
    std::cerr << "Error: Invalid number of arguments.\n\n" << std::endl;
    return ERROR_ARGS;
  }

  const char* inputPath = argv[2];
  const char* outputPath = argv[3];

  std::ifstream input { inputPath };
  if (!input) {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
  }

  size_t rows = 0, cols = 0;
  if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
  }

  size_t totalElements = rows * cols;

  if (totalElements == 0) {
    std::ofstream output { outputPath };
    if (!output) {
        std::cerr << "Error: File error or corrupted data.\n";
        return ERROR_DATA;
    }
    output << 0 << std::endl;
    output << "0 0" << std::endl;
    return SUCCESS;
  }

  int staticArray[10000];
  int* matrix = nullptr;

  if (num == 1) {
    if (totalElements > 10000) {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
    }

    int staticArray[10000];

    for (int i = 0; i < totalElements; ++i) {
      if (!(input >> staticArray[i])) {
          std::cerr << "Error: File error or corrupted data.\n";
          return ERROR_DATA;
      }
    }

    int extra = 0;
    if (input >> extra) {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
  }
  input.close();

  std::ofstream output { outputPath };
  if (!output) {
    std::cerr << "Error: File error or corrupted data.\n";
    return ERROR_DATA;
  }



  return 0;
}
