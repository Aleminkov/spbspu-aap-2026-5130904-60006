#include <limits>
#include <iostream>

namespace aleshin
{
  const int ok = 0;
  const int bad_input = 1;
  const int no_result = 2;
  const unsigned long limit = std::numeric_limits< unsigned long >::max();

  int run()
  {
    bool empty = true;
    bool got_zero = false;

    int max_num = 0;
    unsigned long long max_count = 0;
    bool count_overflow = false;

    int prev = 0;
    unsigned long long cur_run = 0;
    unsigned long long best_run = 0;
    bool run_overflow = false;

    int num = 0;
    while (std::cin >> num)
    {
      if (num == 0)
      {
        got_zero = true;
        break;
      }

      if (empty || num > max_num)
      {
        max_num = num;
        max_count = 1;
        count_overflow = false;
      }
      else if (num == max_num)
      {
        if (max_count == limit)
        {
          count_overflow = true;
        }
        else
        {
          ++max_count;
        }
      }

      if (!empty && num == prev)
      {
        if (cur_run == limit)
        {
          run_overflow = true;
        }
        else
        {
          ++cur_run;
        }
      }
      else
      {
        prev = num;
        cur_run = 1;
      }
      if (cur_run > best_run)
      {
        best_run = cur_run;
      }

      empty = false;
    }

    if (!got_zero)
    {
      std::cerr << "Error: это не последовательность\n";
      return bad_input;
    }

    int code = ok;

    if (empty || count_overflow)
    {
      std::cerr << "Error: невозможно рассчитать CNT-MAX\n";
      code = no_result;
    }
    else
    {
      std::cout << max_count << '\n';
    }

    if (run_overflow)
    {
      std::cerr << "Error: невозможно рассчитать EQL-SEQ\n";
      code = no_result;
    }
    else
    {
      std::cout << best_run << '\n';
    }

    return code;
  }
}

int main()
{
  return aleshin::run();
}
