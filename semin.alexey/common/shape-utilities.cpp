#include "shape-utilities.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "shape-common.hpp"

namespace
{
  constexpr double half = 0.5;

  double checkedAdd(double left, double right)
  {
    const double result = left + right;
    if (!std::isfinite(result))
    {
      throw std::overflow_error("Geometry exceeds double range");
    }
    return result;
  }

  double checkedSubtract(double left, double right)
  {
    const double result = left - right;
    if (!std::isfinite(result))
    {
      throw std::overflow_error("Geometry exceeds double range");
    }
    return result;
  }

  double checkedMultiply(double left, double right)
  {
    const double result = left * right;
    if (!std::isfinite(result))
    {
      throw std::overflow_error("Geometry exceeds double range");
    }
    return result;
  }

  semin::point_t getScaledPosition(const semin::point_t & position, const semin::point_t & center, double factor)
  {
    const double offsetX = checkedSubtract(position.x, center.x);
    const double offsetY = checkedSubtract(position.y, center.y);
    const double scaledX = checkedMultiply(offsetX, factor);
    const double scaledY = checkedMultiply(offsetY, factor);
    const semin::point_t result = {checkedAdd(center.x, scaledX), checkedAdd(center.y, scaledY)};
    return result;
  }

  void validateShapes(semin::Shape * const shapes[], std::size_t count)
  {
    if (shapes == nullptr || count == 0)
    {
      throw std::invalid_argument("At least one shape is required");
    }
    for (std::size_t index = 0; index < count; ++index)
    {
      if (shapes[index] == nullptr)
      {
        throw std::invalid_argument("Shape list contains a null pointer");
      }
    }
  }

  void getBounds(const semin::rectangle_t & frame, double & left, double & right, double & bottom, double & top)
  {
    left = checkedSubtract(frame.pos.x, frame.width * half);
    right = checkedAdd(frame.pos.x, frame.width * half);
    bottom = checkedSubtract(frame.pos.y, frame.height * half);
    top = checkedAdd(frame.pos.y, frame.height * half);
  }
}

void semin::scaleShapes(semin::Shape * const shapes[], std::size_t count, const semin::point_t & center, double factor)
{
  validateShapes(shapes, count);
  semin::detail::validatePoint(center);
  semin::detail::validatePositive(factor, "Scale factor must be positive and finite");

  for (std::size_t index = 0; index < count; ++index)
  {
    const semin::rectangle_t frame = shapes[index]->getFrameRect();
    getScaledPosition(frame.pos, center, factor);
    checkedMultiply(frame.width, factor);
    checkedMultiply(frame.height, factor);
    const double scaledArea = checkedMultiply(shapes[index]->getArea(), factor);
    checkedMultiply(scaledArea, factor);
  }

  for (std::size_t index = 0; index < count; ++index)
  {
    const semin::rectangle_t frame = shapes[index]->getFrameRect();
    const semin::point_t newPosition = getScaledPosition(frame.pos, center, factor);
    shapes[index]->scale(factor);
    shapes[index]->move(newPosition);
  }
}

void semin::printSummary(const char * title,
  semin::Shape * const shapes[], const char * const names[], std::size_t count)
{
  validateShapes(shapes, count);
  if (names == nullptr)
  {
    throw std::invalid_argument("Shape names are required");
  }

  double total_area = 0.0;
  double left = 0.0;
  double right = 0.0;
  double bottom = 0.0;
  double top = 0.0;

  std::cout << title << ":\n";
  for (std::size_t index = 0; index < count; ++index)
  {
    if (names[index] == nullptr)
    {
      throw std::invalid_argument("Shape name list contains a null pointer");
    }
    const double area = shapes[index]->getArea();
    const semin::rectangle_t frame = shapes[index]->getFrameRect();
    total_area = checkedAdd(total_area, area);

    if (index == 0)
    {
      getBounds(frame, left, right, bottom, top);
    }
    else
    {
      double shape_left = 0.0;
      double shape_right = 0.0;
      double shape_bottom = 0.0;
      double shape_top = 0.0;
      getBounds(frame, shape_left, shape_right, shape_bottom, shape_top);
      if (shape_left < left)
      {
        left = shape_left;
      }
      if (shape_right > right)
      {
        right = shape_right;
      }
      if (shape_bottom < bottom)
      {
        bottom = shape_bottom;
      }
      if (shape_top > top)
      {
        top = shape_top;
      }
    }

    std::cout << "  " << names[index] << ": area = " << area << ", frame center = (" << frame.pos.x;
    std::cout << ", " << frame.pos.y << "), width = " << frame.width;
    std::cout << ", height = " << frame.height << "\n";
  }

  const double frameWidth = checkedSubtract(right, left);
  const double frameHeight = checkedSubtract(top, bottom);
  const double frame_center_x = checkedAdd(left * half, right * half);
  const double frame_center_y = checkedAdd(bottom * half, top * half);
  std::cout << "  Total area = " << total_area << "\n";
  std::cout << "  Overall frame center = (" << frame_center_x << ", " << frame_center_y << ")";
  std::cout << ", width = " << frameWidth << ", height = " << frameHeight << "\n";
}
