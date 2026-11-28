#include "../common/shape-utilities.hpp"
#include "../common/shapes/rectangle.hpp"
#include "../common/shapes/ring.hpp"
#include "../common/shapes/xquare.hpp"

#include <cmath>
#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>

namespace
{
  constexpr double rectangle_center_x = 2.0;
  constexpr double rectangle_center_y = 1.0;
  constexpr double rectangle_width = 4.0;
  constexpr double rectangle_height = 3.0;
  constexpr double xquare_center_x = -1.0;
  constexpr double xquare_center_y = 2.0;
  constexpr double xquare_diagonal = 4.0;
  constexpr double ring_center_x = 3.0;
  constexpr double ring_center_y = -2.0;
  constexpr double ring_outer_radius = 3.0;
  constexpr double ring_inner_radius = 1.0;
  constexpr int output_precision = 6;
}

int main()
{
  try
  {
    semin::Rectangle rectangle({rectangle_center_x, rectangle_center_y}, rectangle_width, rectangle_height);
    semin::Xquare xquare({xquare_center_x, xquare_center_y}, xquare_diagonal);
    semin::Ring ring({ring_center_x, ring_center_y}, ring_outer_radius, ring_inner_radius);
    semin::Shape * shapes[] = {&rectangle, &xquare, &ring};
    const char * names[] = {"Rectangle", "Xquare", "Ring"};
    const std::size_t shapeCount = sizeof(shapes) / sizeof(shapes[0]);

    std::cout << std::setprecision(output_precision);
    semin::printSummary("Before scaling", shapes, names, shapeCount);

    double center_x = 0.0;
    double center_y = 0.0;
    double factor = 0.0;
    if (!(std::cin >> center_x >> center_y >> factor))
    {
      std::cerr << "Expected a scale center and a positive scale factor\n";
      return 1;
    }
    if (!std::isfinite(center_x) || !std::isfinite(center_y) || !std::isfinite(factor) || factor <= 0.0)
    {
      std::cerr << "Scale coordinates must be finite and the factor must be positive\n";
      return 1;
    }

    const semin::point_t scale_center = {center_x, center_y};
    semin::scaleShapes(shapes, shapeCount, scale_center, factor);
    semin::printSummary("After scaling", shapes, names, shapeCount);
  }
  catch (const std::exception & error)
  {
    std::cerr << "Geometry error: " << error.what() << "\n";
    return 2;
  }

  return 0;
}
