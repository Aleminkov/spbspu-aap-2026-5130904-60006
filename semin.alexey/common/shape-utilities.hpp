#ifndef SEMIN_SHAPE_UTILITIES_HPP
#define SEMIN_SHAPE_UTILITIES_HPP

#include "shape.hpp"

#include <cstddef>

namespace semin {
void scaleShapes(Shape * const shapes[], std::size_t count,
  const point_t & center, double factor);
void printSummary(const char * title, Shape * const shapes[],
  const char * const names[], std::size_t count);
}

#endif
