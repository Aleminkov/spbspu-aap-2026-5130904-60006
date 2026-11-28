#ifndef SEMIN_RING_HPP
#define SEMIN_RING_HPP

#include "shape.hpp"

namespace semin {
class Ring : public Shape {
public:
  Ring(const point_t & position, double outerRadius, double innerRadius);

  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & position) override;
  void move(double dx, double dy) override;
  void scale(double factor) override;

private:
  point_t position_;
  double outerRadius_;
  double innerRadius_;
};
}

#endif
