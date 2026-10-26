#include <iostream>
#include <limits>
#include <fstream>
#include <stdexcept>

namespace segeev
{
  size_t processVariant9(const int *matrix, size_t rows, size_t cols)
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
        if (nonRepeatingColumnsCount == std::numeric_limits< size_t >::max())
        {
          throw std::overflow_error("");
        }
        nonRepeatingColumnsCount++;
      }
    }
    return nonRepeatingColumnsCount;
  }

  void processVariant6(int *matrix, size_t rows, size_t cols)
  {
    if (rows > 0 && cols > std::numeric_limits< size_t >::max() / rows)
    {
      throw std::overflow_error("");
    }
    size_t totalElements = rows * cols;

    size_t top = 0, bottom = rows - 1;
    size_t left = 0, right = cols - 1;

    size_t current_r = bottom;
    size_t current_c = left;
    int direction = 0;

    for (size_t step = 1; step <= totalElements; ++step)
    {
      if (current_r > 0 && cols > 0 && current_r > std::numeric_limits< size_t >::max() / cols)
      {
        throw std::overflow_error("");
      }
      size_t row_offset = current_r * cols;

      if (row_offset > 0 && current_c > std::numeric_limits< size_t >::max() - row_offset)
      {
        throw std::overflow_error("");
      }
      size_t index = row_offset + current_c;
      if (step > static_cast< size_t >(std::numeric_limits< int >::max()))
      {
        throw std::overflow_error("");
      }
      int int_step = static_cast< int >(step);

      if (matrix[index] > 0 && int_step > std::numeric_limits< int >::max() - matrix[index])
      {
        throw std::overflow_error("");
      }
      if (matrix[index] < 0 && int_step < std::numeric_limits< int >::min() - matrix[index])
      {
        throw std::overflow_error("");
      }
      matrix[index] += int_step;

      if (direction == 0)
      {
        if (current_c < right)
        {
          current_c++;
        }
        else
        {
          if (bottom == 0)
          {
            throw std::overflow_error("");
          }
          bottom--;

          if (current_r == 0)
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
          current_r--;
        }
        else
        {
          if (right == 0)
          {
            throw std::overflow_error("");
          }
          right--;

          if (current_c == 0)
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
          current_c--;
        }
        else
        {
          if (top == std::numeric_limits< size_t >::max())
          {
            throw std::overflow_error("");
          }
          top++;

          if (current_r == std::numeric_limits< size_t >::max())
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
          current_r++;
        }
        else
        {
          if (left == std::numeric_limits< size_t >::max())
          {
            throw std::overflow_error("");
          }
          left++;

          if (current_c == std::numeric_limits< size_t >::max())
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
    std::cerr << "Error: Invalid number of arguments." << std::endl;
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
    std::cerr << "Error: Invalid number of arguments." << std::endl;
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
  if (!(input >> rows >> cols))
  {
    std::cerr << "Error: File error or corrupted data.\n";
    return ERROR_DATA;
  }

  if (rows > 0 && cols > std::numeric_limits< size_t >::max() / rows)
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

    for (size_t i = 0; i < totalElements; ++i)
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

    size_t result9 = 0;
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
    for (size_t i = 0; i < totalElements; ++i)
    {
      output << " " << staticArray[i];
    }
    output << std::endl;
  }
  else
  {
    int *dynamicArray = new (std::nothrow) int[totalElements];
    if (!dynamicArray)
    {
      std::cerr << "Error: File error or corrupted data.\n";
      return ERROR_DATA;
    }

    for (size_t i = 0; i < totalElements; ++i)
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

    size_t result9 = 0;
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
    for (size_t i = 0; i < totalElements; ++i)
    {
      output << " " << dynamicArray[i];
    }
    output << std::endl;

    delete[] dynamicArray;
  }

  return SUCCESS;
}
