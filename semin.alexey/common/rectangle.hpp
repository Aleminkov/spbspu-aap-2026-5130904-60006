#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace semin
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t & position, double width, double height);

    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t & position) override;
    void move(double dx, double dy) override;
    void scale(double factor) override;

  private:
    point_t position_;
    double width_;
    double height_;
  };
}

#endif
