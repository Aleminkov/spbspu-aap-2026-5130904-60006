#ifndef RING_HPP
#define RING_HPP

#include "shape.hpp"

namespace semin
{
  class Ring : public Shape
  {
  public:
    Ring(const point_t & position, double outer_radius, double inner_radius);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & position) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t position_;
    double outer_radius_;
    double inner_radius_;
  };
}

#endif
