#include <iostream>
#include <cstddef>
#include <limits>

namespace braterskaia
{
  const int ERR_INPUT = 1;
  const std::size_t MAX_SZ = std::numeric_limits< std::size_t >::max();
}

int main()
{
  std::size_t inc_cnt = 0;
  std::size_t max_inc = 1;
  std::size_t cur_inc = 1;

  int prev = 0;
  int curr = 0;
  bool is_first = true;
  bool has_error = false;

  while (std::cin >> curr)
  {
    if (curr == 0)
    {
      break;
    }

    if (is_first)
    {
      prev = curr;
      is_first = false;
      continue;
    }

    if (curr > prev)
    {
      if (inc_cnt == braterskaia::MAX_SZ || cur_inc == braterskaia::MAX_SZ)
      {
        std::cerr << "Error: overflow detected\n";
        has_error = true;
        break;
      }

      ++inc_cnt;
      ++cur_inc;

      if (cur_inc > max_inc)
      {
        max_inc = cur_inc;
      }
    }
    else
    {
      cur_inc = 1;
    }

    prev = curr;
  }

  if (!std::cin)
  {
    std::cerr << "Error: invalid input\n";
    has_error = true;
  }

  if (is_first)
  {
    std::cerr << "Error: empty sequence\n";
    has_error = true;
  }

  if (has_error)
  {
    std::cout << "Error" << '\n';
    return braterskaia::ERR_INPUT;
  }

  std::cout << max_inc << '\n';
  std::cout << inc_cnt << '\n';

  return 0;
}
