#include "shapes/rectangle.hpp"

#include "../shape-common.hpp"

semin::Rectangle::Rectangle(const semin::point_t & position, double width, double height):
  position_(position),
  width_(width),
  height_(height)
{
  semin::detail::validatePoint(position_);
  semin::detail::validatePositive(width_, "Rectangle width must be positive and finite");
  semin::detail::validatePositive(height_, "Rectangle height must be positive and finite");
}

double semin::Rectangle::getArea() const
{
  return semin::detail::multiplyFinite(width_, height_, "Rectangle area exceeds double range");
}

semin::rectangle_t semin::Rectangle::getFrameRect() const
{
  const semin::rectangle_t frame = {width_, height_, position_};
  return frame;
}

void semin::Rectangle::move(const semin::point_t & position)
{
  semin::detail::validatePoint(position);
  position_ = position;
}

void semin::Rectangle::move(double dx, double dy)
{
  position_ = semin::detail::movePoint(position_, dx, dy,
    "Rectangle position exceeds double range");
}

void semin::Rectangle::scale(double factor)
{
  semin::detail::validatePositive(factor, "Scale factor must be positive and finite");
  const double width = semin::detail::multiplyFinite(width_, factor,
    "Rectangle width exceeds double range");
  const double height = semin::detail::multiplyFinite(height_, factor,
    "Rectangle height exceeds double range");
  width_ = width;
  height_ = height;
}
