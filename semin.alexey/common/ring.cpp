#include "ring.hpp"

#include <stdexcept>

#include "shape-common.hpp"

semin::Ring::Ring(const semin::point_t & position, double outerRadius, double innerRadius):
  position_(position),
  outerRadius_(outerRadius),
  innerRadius_(innerRadius)
{
  semin::detail::validatePoint(position_);
  semin::detail::validatePositive(outerRadius_, "Ring outer radius must be positive and finite");
  semin::detail::validatePositive(innerRadius_, "Ring inner radius must be positive and finite");
  if (innerRadius_ >= outerRadius_) {
    throw std::invalid_argument("Ring inner radius must be smaller than its outer radius");
  }
}

double semin::Ring::getArea() const
{
  const double outerSquare = semin::detail::multiplyFinite(outerRadius_, outerRadius_,
    "Ring area exceeds double range");
  const double innerSquare = semin::detail::multiplyFinite(innerRadius_, innerRadius_,
    "Ring area exceeds double range");
  return semin::detail::multiplyFinite(3.14159265358979323846,
    outerSquare - innerSquare, "Ring area exceeds double range");
}

semin::rectangle_t semin::Ring::getFrameRect() const
{
  const double diameter = semin::detail::multiplyFinite(outerRadius_, 2.0,
    "Ring diameter exceeds double range");
  const semin::rectangle_t frame = {diameter, diameter, position_};
  return frame;
}

void semin::Ring::move(const semin::point_t & position)
{
  semin::detail::validatePoint(position);
  position_ = position;
}

void semin::Ring::move(double dx, double dy)
{
  position_ = semin::detail::movePoint(position_, dx, dy,
    "Ring position exceeds double range");
}

void semin::Ring::scale(double factor)
{
  semin::detail::validatePositive(factor, "Scale factor must be positive and finite");
  const double outerRadius = semin::detail::multiplyFinite(outerRadius_, factor,
    "Ring outer radius exceeds double range");
  const double innerRadius = semin::detail::multiplyFinite(innerRadius_, factor,
    "Ring inner radius exceeds double range");
  outerRadius_ = outerRadius;
  innerRadius_ = innerRadius;
}
