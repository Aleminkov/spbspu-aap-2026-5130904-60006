#include <iostream>
#include <limits>
#include <fstream>
#include <exception>

namespace segeev
{
  int processVariant9(const int *matrix, int rows, int cols)
  {
    if (rows <= 1)
    {
      return cols;
    }

    size_t nonRepeatingColumnsCount = 0;

    for (size_t i = 0; i < cols; ++i)
    {
      bool hasDuplicates = false;
      for (size_t j = 0; j < rows - 1; ++j)
      {
        if (matrix[j * cols + i] == matrix[(j + 1) * cols + i])
        {
          hasDuplicates = true;
          break;
        }
      }
      if (!hasDuplicates)
      {
        if (nonRepeatingColumnsCount > std::numeric_limits< size_t >::max() - 1)
        {
          throw std::overflow_error("");
        }
        nonRepeatingColumnsCount++;
      }
    }
    return nonRepeatingColumnsCount;
  }

  void processVariant6(int *matrix, int rows, int cols)
  {
    int totalElements = rows * cols;
    int top = 0, bottom = rows - 1;
    int left = 0, right = cols - 1;

    int current_r = bottom;
    int current_c = left;
    int direction = 0;

    for (int step = 1; step <= totalElements; ++step)
    {
      if (current_r > 0 && cols > 0 && current_r > std::numeric_limits< int >::max() / cols)
      {
        throw std::overflow_error("");
      }
      int row_offset = current_r * cols;

      if (row_offset > 0 && current_c > std::numeric_limits< int >::max() - row_offset)
      {
        throw std::overflow_error("");
      }
      int index = row_offset + current_c;

      if (matrix[index] > 0 && step > std::numeric_limits< int >::max() - matrix[index])
      {
        throw std::overflow_error("");
      }
      if (matrix[index] < 0 && step < std::numeric_limits< int >::min() - matrix[index])
      {
        throw std::overflow_error("");
      }
      matrix[index] += step;

      if (direction == 0)
      {
        if (current_c < right)
        {
          if (current_c > std::numeric_limits< int >::max() - 1)
          {
            throw std::overflow_error("");
          }
          current_c++;
        }
        else
        {
          if (bottom < std::numeric_limits< int >::min() + 1)
          {
            throw std::overflow_error("");
          }
          bottom--;

          if (current_r < std::numeric_limits< int >::min() + 1)
          {
            throw std::overflow_error("");
          }
          current_r--;
          direction = 1;
        }
      }
      else if (direction == 1)
      {
        if (current_r > top)
        {
          if (current_r < std::numeric_limits< int >::min() + 1)
          {
            throw std::overflow_error("");
          }
          current_r--;
        }
        else
        {
          if (right < std::numeric_limits< int >::min() + 1)
          {
            throw std::overflow_error("");
          }
          right--;

          if (current_c < std::numeric_limits< int >::min() + 1)
          {
            throw std::overflow_error("");
          }
          current_c--;
          direction = 2;
        }
      }
      else if (direction == 2)
      {
        if (current_c > left)
        {
          if (current_c < std::numeric_limits< int >::min() + 1)
          {
            throw std::overflow_error("");
          }
          current_c--;
        }
        else
        {
          if (top > std::numeric_limits< int >::max() - 1)
          {
            throw std::overflow_error("");
          }
          top++;

          if (current_r > std::numeric_limits< int >::max() - 1)
          {
            throw std::overflow_error("");
          }
          current_r++;
          direction = 3;
        }
      }
      else if (direction == 3)
      {
        if (current_r < bottom)
        {
          if (current_r > std::numeric_limits< int >::max() - 1)
          {
            throw std::overflow_error("");
          }
          current_r++;
        }
        else
        {
          if (left > std::numeric_limits< int >::max() - 1)
          {
            throw std::overflow_error("");
          }
          left++;

          if (current_c > std::numeric_limits< int >::max() - 1)
          {
            throw std::overflow_error("");
          }
          current_c++;
          direction = 0;
        }
      }
    }
  }
}

int main(int argc, char **argv)
{
  const int SUCCESS = 0;
  const int ERROR_ARGS = 1;
  const int ERROR_DATA = 2;

  if (argc != 4)
  {
    std::cerr << "Error: Invalid number of arguments.\n" << std::endl;
    return ERROR_ARGS;
  }

  int num = 0;

  if (argv[1][0] == '1' && argv[1][1] == '\0')
  {
    num = 1;
  }
  else if (argv[1][0] == '2' && argv[1][1] == '\0')
  {
    num = 2;
  }
  else
  {
    std::cerr << "Error: Invalid number of arguments.\n" << std::endl;
    return ERROR_ARGS;
  }

  const char *inputPath = argv[2];
  const char *outputPath = argv[3];

  std::ifstream input{inputPath};
  if (!input)
  {
    std::cerr << "Error: File error or corrupted data.\n";
    return ERROR_DATA;
  }

  size_t rows = 0, cols = 0;
  if (!(input >> rows >> cols) || rows < 0 || cols < 0)
  {
    std::cerr << "Error: File error or corrupted data.\n";
    return ERROR_DATA;
  }

  size_t totalElements = rows * cols;

  if (totalElements == 0)
  {
    std::ofstream output{outputPath};
    if (!output)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
    }
    output << 0 << std::endl;
    output << "0 0" << std::endl;
    return SUCCESS;
  }

  if (num == 1)
  {
    if (totalElements > 10000)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
    }

    int staticArray[10000];

    for (int i = 0; i < totalElements; ++i)
    {
      if (!(input >> staticArray[i]))
      {
        std::cerr << "Error: File error or corrupted data.\n";
        return ERROR_DATA;
      }
    }

    int extra = 0;
    if (input >> extra)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
    }
    input.close();

    int result9 = 0;
    try
    {
      result9 = segeev::processVariant9(staticArray, rows, cols);
      segeev::processVariant6(staticArray, rows, cols);
    }
    catch (const std::overflow_error &)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
    }

    std::ofstream output{outputPath};
    if (!output)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
    }

    output << result9 << std::endl;
    output << rows << " " << cols;
    for (int i = 0; i < totalElements; ++i)
    {
      output << " " << staticArray[i];
    }
    output << std::endl;
  }
  else
  {
    int *dynamicArray = new int[totalElements];

    for (int i = 0; i < totalElements; ++i)
    {
      if (!(input >> dynamicArray[i]))
      {
        std::cerr << "Error: File error or corrupted data.\n";
        delete[] dynamicArray;
        return ERROR_DATA;
      }
    }

    int extra;
    if (input >> extra)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      delete[] dynamicArray;
      return ERROR_DATA;
    }
    input.close();

    int result9 = 0;
    try
    {
      result9 = segeev::processVariant9(dynamicArray, rows, cols);
      segeev::processVariant6(dynamicArray, rows, cols);
    }
    catch (const std::overflow_error &)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      delete[] dynamicArray;
      return ERROR_DATA;
    }

    std::ofstream output{outputPath};
    if (!output)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      delete[] dynamicArray;
      return ERROR_DATA;
    }

    output << result9 << std::endl;
    output << rows << " " << cols;
    for (int i = 0; i < totalElements; ++i)
    {
      output << " " << dynamicArray[i];
    }
    output << std::endl;

    delete[] dynamicArray;
  }

  return SUCCESS;
}
