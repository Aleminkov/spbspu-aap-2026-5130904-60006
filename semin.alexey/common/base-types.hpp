#ifndef SEMIN_BASE_TYPES_HPP
#define SEMIN_BASE_TYPES_HPP

namespace semin {
struct point_t {
  double x;
  double y;
};

struct rectangle_t {
  double width;
  double height;
  point_t pos;
};
}

#endif
