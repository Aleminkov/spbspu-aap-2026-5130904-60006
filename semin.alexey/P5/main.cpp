#include "../common/rectangle.hpp"
#include "../common/ring.hpp"
#include "../common/shape-utilities.hpp"
#include "../common/xquare.hpp"

#include <cmath>
#include <cstddef>
#include <exception>
#include <iomanip>
#include <iostream>

int main()
{
  double centerX = 0.0;
  double centerY = 0.0;
  double factor = 0.0;
  if (!(std::cin >> centerX >> centerY >> factor))
  {
    std::cerr << "Expected a scale center and a positive scale factor\n";
    return 1;
  }
  if (!std::isfinite(centerX) || !std::isfinite(centerY) || !std::isfinite(factor) || factor <= 0.0)
  {
    std::cerr << "Scale coordinates must be finite and the factor must be positive\n";
    return 1;
  }

  try
  {
    const semin::point_t scaleCenter = {centerX, centerY};
    semin::Rectangle rectangle({2.0, 1.0}, 4.0, 3.0);
    semin::Xquare xquare({-1.0, 2.0}, 4.0);
    semin::Ring ring({3.0, -2.0}, 3.0, 1.0);
    semin::Shape * shapes[] = {&rectangle, &xquare, &ring};
    const char * names[] = {"Rectangle", "Xquare", "Ring"};
    const std::size_t shapeCount = sizeof(shapes) / sizeof(shapes[0]);

    std::cout << std::setprecision(6);
    semin::printSummary("Before scaling", shapes, names, shapeCount);
    semin::scaleShapes(shapes, shapeCount, scaleCenter, factor);
    semin::printSummary("After scaling", shapes, names, shapeCount);
  }
  catch (const std::exception & error)
  {
    std::cerr << "Geometry error: " << error.what() << "\n";
    return 2;
  }

  return 0;
}
