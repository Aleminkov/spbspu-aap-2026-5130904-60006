#include "shapes/xquare.hpp"

#include "shape-common.hpp"

namespace
{
  constexpr double half = 0.5;
}

semin::Xquare::Xquare(const semin::point_t & position, double diagonal):
  position_(position),
  diagonal_(diagonal)
{
  semin::detail::validatePoint(position_);
  semin::detail::validatePositive(diagonal_, "Xquare diagonal must be positive and finite");
}

double semin::Xquare::getArea() const
{
  return semin::detail::multiplyFinite(diagonal_, diagonal_,
    "Xquare area exceeds double range") * half;
}

semin::rectangle_t semin::Xquare::getFrameRect() const
{
  const semin::rectangle_t frame = {diagonal_, diagonal_, position_};
  return frame;
}

void semin::Xquare::move(const semin::point_t & position)
{
  semin::detail::validatePoint(position);
  position_ = position;
}

void semin::Xquare::move(double dx, double dy)
{
  position_ = semin::detail::movePoint(position_, dx, dy,
    "Xquare position exceeds double range");
}

void semin::Xquare::scale(double factor)
{
  semin::detail::validatePositive(factor, "Scale factor must be positive and finite");
  diagonal_ = semin::detail::multiplyFinite(diagonal_, factor,
    "Xquare diagonal exceeds double range");
}
