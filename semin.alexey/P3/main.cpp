#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <limits>
#include <new>
#include <stdexcept>

int main(int argc, char** argv)
{
  const int err_args = 1;
  const int err_data = 2;
  constexpr std::size_t max_fixed_size = 10000;

  if (argc != 4)
  {
    std::cerr << "Неверное количество аргументов командной строки\n";
    return err_args;
  }

  char* end_ptr = nullptr;
  const long num = std::strtol(argv[1], &end_ptr, 10);
  if (*argv[1] == '\0' || *end_ptr != '\0' || (num != 1 && num != 2))
  {
    std::cerr << "Неверный первый параметр командной строки\n";
    return err_args;
  }

  std::ifstream input(argv[2]);
  if (!input.is_open())
  {
    std::cerr << "Не удалось открыть входной файл\n";
    return err_data;
  }

  long long row_count = 0;
  long long column_count = 0;
  if (!(input >> row_count >> column_count) || row_count < 0 || column_count < 0
      || ((row_count == 0) != (column_count == 0)))
  {
    std::cerr << "Неверные размеры матрицы во входном файле\n";
    return err_data;
  }

  const unsigned long long max_size = static_cast< unsigned long long >(std::numeric_limits< std::size_t >::max());
  if (static_cast< unsigned long long >(row_count) > max_size
      || static_cast< unsigned long long >(column_count) > max_size)
  {
    std::cerr << "Переполнение размеров матрицы\n";
    return err_data;
  }

  const std::size_t rows = static_cast< std::size_t >(row_count);
  const std::size_t cols = static_cast< std::size_t >(column_count);
  if (rows > 0 && cols > std::numeric_limits< std::size_t >::max() / rows)
  {
    std::cerr << "Переполнение размеров матрицы\n";
    return err_data;
  }

  const std::size_t total = rows * cols;
  if (num == 1 && total > max_fixed_size)
  {
    std::cerr << "Размер матрицы превышает лимит для статического массива\n";
    return err_data;
  }
  if (total > std::numeric_limits< std::size_t >::max() / sizeof(int)
      || cols > std::numeric_limits< std::size_t >::max() / sizeof(int)
      || static_cast< unsigned long long >(total)
          > static_cast< unsigned long long >(std::numeric_limits< long long >::max()))
  {
    std::cerr << "Переполнение размеров матрицы\n";
    return err_data;
  }

  int fixed_matrix[max_fixed_size]{};
  int* dyn_matrix = nullptr;
  int* matrix = fixed_matrix;
  if (num == 2 && total > 0)
  {
    try
    {
      dyn_matrix = new int[total];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Ошибка выделения динамической памяти\n";
      return err_data;
    }
    matrix = dyn_matrix;
  }

  bool valid_matrix = true;
  for (std::size_t index = 0; index < total; ++index)
  {
    if (!(input >> matrix[index]))
    {
      valid_matrix = false;
      break;
    }
  }
  if (!valid_matrix)
  {
    std::cerr << "Не удалось прочитать элементы матрицы\n";
    delete[] dyn_matrix;
    return err_data;
  }

  input.close();

  int fixed_column_maxima[max_fixed_size]{};
  int* dyn_column_maxima = nullptr;
  int* column_maxima = fixed_column_maxima;
  if (num == 2 && cols > 0)
  {
    try
    {
      dyn_column_maxima = new int[cols];
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "Ошибка выделения памяти для максимумов столбцов\n";
      delete[] dyn_matrix;
      return err_data;
    }
    column_maxima = dyn_column_maxima;
  }

  for (std::size_t column = 0; column < cols; ++column)
  {
    column_maxima[column] = matrix[column];
    for (std::size_t row = 1; row < rows; ++row)
    {
      const int value = matrix[row * cols + column];
      if (value > column_maxima[column])
      {
        column_maxima[column] = value;
      }
    }
  }

  std::size_t saddle_point_count = 0;
  for (std::size_t row = 0; row < rows; ++row)
  {
    int row_minimum = matrix[row * cols];
    for (std::size_t column = 1; column < cols; ++column)
    {
      const int value = matrix[row * cols + column];
      if (value < row_minimum)
      {
        row_minimum = value;
      }
    }

    for (std::size_t column = 0; column < cols; ++column)
    {
      const int value = matrix[row * cols + column];
      if (value == row_minimum && value == column_maxima[column])
      {
        ++saddle_point_count;
      }
    }
  }

  try
  {
    if (rows > 0 && cols > 0)
    {
      std::size_t top = 0;
      std::size_t bottom = rows - 1;
      std::size_t left = 0;
      std::size_t right = cols - 1;
      long long row = 0;
      long long column = 0;
      long long row_direction = 0;
      long long column_direction = 1;

      for (std::size_t index = 0; index < total; ++index)
      {
        const long long step = static_cast< long long >(index) + 1;
        const std::size_t matrix_row = static_cast< std::size_t >(row);
        const std::size_t matrix_column = static_cast< std::size_t >(column);
        const std::size_t matrix_index = matrix_row * cols + matrix_column;
        const long long value = matrix[matrix_index];
        const long long min_value = std::numeric_limits< int >::min();
        if (step > value - min_value)
        {
          throw std::overflow_error("Переполнение при изменении элемента матрицы");
        }
        matrix[matrix_index] = static_cast< int >(value - step);

        if (index + 1 == total)
        {
          break;
        }

        if (column_direction == 1 && static_cast< std::size_t >(column) == right)
        {
          ++top;
          row_direction = 1;
          column_direction = 0;
        }
        else if (row_direction == 1 && static_cast< std::size_t >(row) == bottom)
        {
          --right;
          row_direction = 0;
          column_direction = -1;
        }
        else if (column_direction == -1 && static_cast< std::size_t >(column) == left)
        {
          --bottom;
          row_direction = -1;
          column_direction = 0;
        }
        else if (row_direction == -1 && static_cast< std::size_t >(row) == top)
        {
          ++left;
          row_direction = 0;
          column_direction = 1;
        }

        row += row_direction;
        column += column_direction;
      }
    }
  }
  catch (const std::overflow_error& error)
  {
    std::cerr << error.what() << "\n";
    delete[] dyn_column_maxima;
    delete[] dyn_matrix;
    return err_data;
  }

  std::ofstream output(argv[3]);
  if (!output.is_open())
  {
    std::cerr << "Не удалось открыть выходной файл для записи\n";
    delete[] dyn_column_maxima;
    delete[] dyn_matrix;
    return err_data;
  }

  output << saddle_point_count << "\n";
  output << rows << " " << cols;
  for (std::size_t index = 0; index < total; ++index)
  {
    output << " " << matrix[index];
  }
  output << "\n";

  const bool output_is_good = output.good();
  output.close();
  delete[] dyn_column_maxima;
  delete[] dyn_matrix;

  if (!output_is_good)
  {
    std::cerr << "Ошибка записи в выходной файл\n";
    return err_data;
  }

  return 0;
}
