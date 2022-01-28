#include "common.h"
#include "math.h"

sf::Vector2f CommonObject::unitAtAngle(double angle) {
  return sf::Vector2f(cos(angle), sin(angle));
}

double CommonObject::getDistance(sf::Vector2i a, sf::Vector2i b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double CommonObject::getDistance(sf::Vector2f a, sf::Vector2i b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double CommonObject::getDistance(sf::Vector2f a, sf::Vector2f b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double CommonObject::getAngle(sf::Vector2i a, sf::Vector2i b) {
  double dot = (a.x * b.x) + (a.y * b.y);
  double prod = sqrt(pow(a.x, 2) + pow(a.y, 2)) * sqrt(pow(b.x, 2) + pow(b.y, 2));
  double res = std::min(1.0, dot/prod);
  return acos(res);
}

double CommonObject::getAngle(sf::Vector2f a, sf::Vector2f b) {
  double dot = (a.x * b.x) + (a.y * b.y);
  double prod = sqrt(pow(a.x, 2) + pow(a.y, 2)) * sqrt(pow(b.x, 2) + pow(b.y, 2));
  double res = std::min(1.0, dot/prod);
  return acos(res);
}

bool CommonObject::solveQuadratic(double a, double b, double c, double *roots) {
  // Solve generic Ax^2 + Bx + C = 0
  if (a == 0) {
    return false;
  }
  double delta = pow(b, 2) - 4*a*c;
  if (delta < 0) {
    // No real solution - empty solution
    return false;
  }
  // Solve with x = (-b +/- sqrt(delta)) / 2a
  roots[0] = (-b + sqrt(delta)) / (2*a);
  roots[1] = (-b - sqrt(delta)) / (2*a);
  return true;
}

bool CommonObject::solveLineCircleIntersect(
  double *lineParams,
  sf::Vector2i center,
  double radius,
  sf::Vector2f *solutions
) {
  // Convert line and circle params to quadratic equation to solve intersection
  // Line ax+by=1
  // Circle (x-x0)^2 + (y-y0)^2 = r^2
  // Solution is generic Ax^2+Bx+C=0
  // A = b^2 + a^2
  // B = -2 * (x0*(b^2) + a*(1-b*y0))
  // C = (b^2)*(x0^2 + y0^2 - r^2) - 2*b*y0 + 1
  double a = lineParams[0];
  double b = lineParams[1];
  double bTwo = pow(b, 2);
  double x = center.x;
  double y = center.y;
  double quadA = bTwo + pow(a, 2);
  double quadB = -2*(bTwo*x + a*(1-b*y));
  double aux = pow(x, 2)+pow(y, 2)-pow(radius, 2);
  double quadC = bTwo*aux - 2*b*y + 1;
  double roots[2];
  bool hasRoots = solveQuadratic(quadA, quadB, quadC, roots);
  if (!hasRoots) {
    // No real roots, no intersection - empty solution
    return false;
  }
  // Compute solutions based on line equation, except if vertical line,
  // then use the circle equation
  if (b == 0) {
    quadA = 1;
    quadB = -2*y;
    quadC = aux - 2*x*roots[0] + pow(roots[0], 2);
    double yroots[2];
    solveQuadratic(quadA, quadB, quadC, yroots);
    solutions[0] = sf::Vector2f(roots[0], yroots[0]);
    solutions[1] = sf::Vector2f(roots[0], yroots[1]);
  } else {
    solutions[0] = sf::Vector2f(roots[0], ((1 - a*roots[0])/b));
    solutions[1] = sf::Vector2f(roots[1], ((1 - a*roots[1])/b));
  }
  return true;
}

std::string CommonObject::padIntToString(long value, unsigned int size, char padding) {
  std::string str = std::to_string(value);
  unsigned int current = str.size();
  if (size > current) {
    str.insert(0, size-current, padding);
  }
  return str;
}
