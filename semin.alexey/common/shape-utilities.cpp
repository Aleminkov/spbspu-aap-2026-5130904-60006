#include "shape-utilities.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>

#include "shape-common.hpp"

namespace {
double checkedAdd(double left, double right)
{
  const double result = left + right;
  if (!std::isfinite(result)) {
    throw std::overflow_error("Geometry exceeds double range");
  }
  return result;
}

double checkedSubtract(double left, double right)
{
  const double result = left - right;
  if (!std::isfinite(result)) {
    throw std::overflow_error("Geometry exceeds double range");
  }
  return result;
}

double checkedMultiply(double left, double right)
{
  const double result = left * right;
  if (!std::isfinite(result)) {
    throw std::overflow_error("Geometry exceeds double range");
  }
  return result;
}

semin::point_t getScaledPosition(const semin::point_t & position,
  const semin::point_t & center, double factor)
{
  const double offsetX = checkedSubtract(position.x, center.x);
  const double offsetY = checkedSubtract(position.y, center.y);
  const double scaledX = checkedMultiply(offsetX, factor);
  const double scaledY = checkedMultiply(offsetY, factor);
  const semin::point_t result = {
    checkedAdd(center.x, scaledX),
    checkedAdd(center.y, scaledY)
  };
  return result;
}

void validateShapes(semin::Shape * const shapes[], std::size_t count)
{
  if (shapes == nullptr || count == 0) {
    throw std::invalid_argument("At least one shape is required");
  }
  for (std::size_t index = 0; index < count; ++index) {
    if (shapes[index] == nullptr) {
      throw std::invalid_argument("Shape list contains a null pointer");
    }
  }
}

void getBounds(const semin::rectangle_t & frame, double & left, double & right,
  double & bottom, double & top)
{
  left = checkedSubtract(frame.pos.x, frame.width / 2.0);
  right = checkedAdd(frame.pos.x, frame.width / 2.0);
  bottom = checkedSubtract(frame.pos.y, frame.height / 2.0);
  top = checkedAdd(frame.pos.y, frame.height / 2.0);
}
}

void semin::scaleShapes(semin::Shape * const shapes[], std::size_t count,
  const semin::point_t & center, double factor)
{
  validateShapes(shapes, count);
  semin::detail::validatePoint(center);
  semin::detail::validatePositive(factor, "Scale factor must be positive and finite");

  for (std::size_t index = 0; index < count; ++index) {
    const semin::rectangle_t frame = shapes[index]->getFrameRect();
    getScaledPosition(frame.pos, center, factor);
    checkedMultiply(frame.width, factor);
    checkedMultiply(frame.height, factor);
    const double scaledArea = checkedMultiply(shapes[index]->getArea(), factor);
    checkedMultiply(scaledArea, factor);
  }

  for (std::size_t index = 0; index < count; ++index) {
    const semin::rectangle_t frame = shapes[index]->getFrameRect();
    const semin::point_t newPosition = getScaledPosition(frame.pos, center, factor);
    shapes[index]->scale(factor);
    shapes[index]->move(newPosition);
  }
}

void semin::printSummary(const char * title, semin::Shape * const shapes[],
  const char * const names[], std::size_t count)
{
  validateShapes(shapes, count);
  if (names == nullptr) {
    throw std::invalid_argument("Shape names are required");
  }

  double totalArea = 0.0;
  double left = 0.0;
  double right = 0.0;
  double bottom = 0.0;
  double top = 0.0;

  std::cout << title << ":\n";
  for (std::size_t index = 0; index < count; ++index) {
    if (names[index] == nullptr) {
      throw std::invalid_argument("Shape name list contains a null pointer");
    }
    const double area = shapes[index]->getArea();
    const semin::rectangle_t frame = shapes[index]->getFrameRect();
    totalArea = checkedAdd(totalArea, area);

    if (index == 0) {
      getBounds(frame, left, right, bottom, top);
    } else {
      double shapeLeft = 0.0;
      double shapeRight = 0.0;
      double shapeBottom = 0.0;
      double shapeTop = 0.0;
      getBounds(frame, shapeLeft, shapeRight, shapeBottom, shapeTop);
      if (shapeLeft < left) {
        left = shapeLeft;
      }
      if (shapeRight > right) {
        right = shapeRight;
      }
      if (shapeBottom < bottom) {
        bottom = shapeBottom;
      }
      if (shapeTop > top) {
        top = shapeTop;
      }
    }

    std::cout << "  " << names[index] << ": area = " << area
      << ", frame center = (" << frame.pos.x << ", " << frame.pos.y << ")"
      << ", width = " << frame.width << ", height = " << frame.height << "\n";
  }

  const double frameWidth = checkedSubtract(right, left);
  const double frameHeight = checkedSubtract(top, bottom);
  const double frameCenterX = checkedAdd(left / 2.0, right / 2.0);
  const double frameCenterY = checkedAdd(bottom / 2.0, top / 2.0);
  std::cout << "  Total area = " << totalArea << "\n";
  std::cout << "  Overall frame center = (" << frameCenterX << ", " << frameCenterY << ")"
    << ", width = " << frameWidth << ", height = " << frameHeight << "\n";
}
