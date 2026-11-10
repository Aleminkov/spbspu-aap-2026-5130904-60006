#include <cstddef>
#include <iostream>
#include <limits>
#include <stdexcept>

namespace podvalnyj
{
  const int ERROR_SEQUENCE = 1;
  const int ERROR_CHARACTERISTIC = 2;

  bool proverka(int & number)
  {
    std::cin >> number;
    return !std::cin.fail();
  }

  bool proverkaPosleNulya()
  {
    char symbol = 0;
    std::cin >> symbol;
    return std::cin.eof();
  }

  bool localMax(int left, int middle, int right)
  {
    return middle > left && middle > right;
  }

  void increment(std::size_t & counter, bool & overflow)
  {
    if (counter == std::numeric_limits< std::size_t >::max())
    {
      overflow = true;
    }
    else
    {
      ++counter;
    }
  }

  void updateAfterMax(int tekuchiy, int & maximum, std::size_t & after_max_count, bool & overflow, bool first)
  {
    if (first || tekuchiy > maximum)
    {
      maximum = tekuchiy;
      after_max_count = 0;
      overflow = false;
    }
    else
    {
      increment(after_max_count, overflow);
    }
  }

  bool process(std::size_t & count, std::size_t & local_max_count, bool & local_overflow, std::size_t & after_max_count,
      bool & after_overflow)
  {
    int tekuchiy = 0;
    int pred = 0;
    int before_pred = 0;
    int maximum = 0;

    while (proverka(tekuchiy) && tekuchiy != 0)
    {
      if (count == 2 && localMax(before_pred, pred, tekuchiy))
      {
        increment(local_max_count, local_overflow);
      }
      updateAfterMax(tekuchiy, maximum, after_max_count, after_overflow, count == 0);
      before_pred = pred;
      pred = tekuchiy;
      if (count < 2)
      {
        ++count;
      }
    }
    if (std::cin.fail())
    {
      return false;
    }
    return proverkaPosleNulya();
  }

  std::size_t getResult(std::size_t count, std::size_t result, bool overflow)
  {
    if (count == 0)
    {
      throw std::logic_error("empty sequence");
    }
    if (overflow)
    {
      throw std::overflow_error("too many elements");
    }
    return result;
  }

  int printResult(const char * name, std::size_t count, std::size_t result, bool overflow)
  {
    try
    {
      std::cout << getResult(count, result, overflow) << "\n";
    }
    catch (const std::logic_error & e)
    {
      std::cerr << name << " error: " << e.what() << "\n";
      return ERROR_CHARACTERISTIC;
    }
    catch (const std::overflow_error & e)
    {
      std::cerr << name << " error: " << e.what() << "\n";
      return ERROR_CHARACTERISTIC;
    }
    return 0;
  }
}

int main()
{
  std::size_t count = 0;
  std::size_t local_max_count = 0;
  std::size_t after_max_count = 0;
  bool local_overflow = false;
  bool after_overflow = false;

  if (!podvalnyj::process(count, local_max_count, local_overflow, after_max_count, after_overflow))
  {
    std::cerr << "Error: invalid sequence\n";
    return podvalnyj::ERROR_SEQUENCE;
  }

  const int local_result = podvalnyj::printResult("LOC-MAX", count, local_max_count, local_overflow);
  const int after_result = podvalnyj::printResult("AFT-MAX", count, after_max_count, after_overflow);

  if (local_result != 0 || after_result != 0)
  {
    return podvalnyj::ERROR_CHARACTERISTIC;
  }
  return 0;
}
