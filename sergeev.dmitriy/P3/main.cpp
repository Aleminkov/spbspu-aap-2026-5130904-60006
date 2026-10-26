#include <iostream>
#include <limits>
#include <fstream>
namespace segeev{
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

  int rows = 0, cols = 0;
  if (!(input >> rows >> cols) || rows < 0 || cols < 0) {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
  }

  int totalElements = rows * cols;

  return 0;
}
