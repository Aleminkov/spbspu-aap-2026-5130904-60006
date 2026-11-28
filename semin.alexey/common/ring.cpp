#include "shapes/ring.hpp"

#include <stdexcept>

#include "shape-common.hpp"

namespace
{
  constexpr double pi = 3.14159265358979323846;
  constexpr double diameter_factor = 2.0;
}

semin::Ring::Ring(const semin::point_t & position, double outer_radius, double inner_radius):
  position_(position),
  outer_radius_(outer_radius),
  inner_radius_(inner_radius)
{
  semin::detail::validatePoint(position_);
  semin::detail::validatePositive(outer_radius_, "Ring outer radius must be positive and finite");
  semin::detail::validatePositive(inner_radius_, "Ring inner radius must be positive and finite");
  if (inner_radius_ >= outer_radius_)
  {
    throw std::invalid_argument("Ring inner radius must be smaller than its outer radius");
  }
}

double semin::Ring::getArea() const
{
  const double outer_square =
    semin::detail::multiplyFinite(outer_radius_, outer_radius_, "Ring area exceeds double range");
  const double inner_square =
    semin::detail::multiplyFinite(inner_radius_, inner_radius_, "Ring area exceeds double range");
  return semin::detail::multiplyFinite(pi, outer_square - inner_square, "Ring area exceeds double range");
}

semin::rectangle_t semin::Ring::getFrameRect() const
{
  const double diameter =
    semin::detail::multiplyFinite(outer_radius_, diameter_factor, "Ring diameter exceeds double range");
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
  position_ = semin::detail::movePoint(position_, dx, dy, "Ring position exceeds double range");
}

void semin::Ring::scale(double factor)
{
  semin::detail::validatePositive(factor, "Scale factor must be positive and finite");
  const double outer_radius =
    semin::detail::multiplyFinite(outer_radius_, factor, "Ring outer radius exceeds double range");
  const double inner_radius =
    semin::detail::multiplyFinite(inner_radius_, factor, "Ring inner radius exceeds double range");
  outer_radius_ = outer_radius;
  inner_radius_ = inner_radius;
}
