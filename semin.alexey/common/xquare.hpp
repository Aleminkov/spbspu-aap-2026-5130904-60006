#ifndef SEMIN_XQUARE_HPP
#define SEMIN_XQUARE_HPP

#include "shape.hpp"

namespace semin {
class Xquare : public Shape {
public:
  Xquare(const point_t & position, double diagonal);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & position) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  point_t position_;
  double diagonal_;
};
}

#endif
