#ifndef SEMIN_SHAPE_COMMON_HPP
#define SEMIN_SHAPE_COMMON_HPP

#include "base-types.hpp"

#include <cmath>
#include <stdexcept>

namespace semin {
namespace detail {
inline void validatePoint(const point_t & position)
{
  if (!std::isfinite(position.x) || !std::isfinite(position.y)) {
    throw std::invalid_argument("Point coordinates must be finite");
  }
}

inline void validatePositive(double value, const char * message)
{
  if (!std::isfinite(value) || value <= 0.0) {
    throw std::invalid_argument(message);
  }
}

inline double multiplyFinite(double left, double right, const char * message)
{
  const double result = left * right;
  if (!std::isfinite(result)) {
    throw std::overflow_error(message);
  }
  return result;
}

inline void validateOffset(double dx, double dy)
{
  if (!std::isfinite(dx) || !std::isfinite(dy)) {
    throw std::invalid_argument("Move offsets must be finite");
  }
}

inline point_t movePoint(const point_t & position, double dx, double dy,
  const char * message)
{
  validateOffset(dx, dy);
  const point_t result = {position.x + dx, position.y + dy};
  if (!std::isfinite(result.x) || !std::isfinite(result.y)) {
    throw std::overflow_error(message);
  }
  return result;
}
}
}

#endif
