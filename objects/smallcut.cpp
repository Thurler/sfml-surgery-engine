#include "smallcut.h"
#include "math.h"

double SmallCut::collide(Ripple *ripple) {
  sf::Vector2i center = ripple->getCenter();
  double distA = getDistance(positionA, center);
  double distB = getDistance(positionB, center);
  unsigned int radius = ripple->effectiveRadius();
  bool inA = (distA <= radius);
  bool inB = (distB <= radius);
  sf::Vector2f pivot;
  if (inA && inB) {
    // Both ends are inside the circle, so we know 100% of it is covered
    return 1;
  } else if (!inA && !inB) {
    // At least one end of the segment must be inside the circle
    return 0;
  } else if (inA) {
    // Use point A as pivot
    pivot = positionA;
  } else {
    // Use point B as pivot
    pivot = positionB;
  }
  // Solve intersection of line and circle
  sf::Vector2f solutions[2];
  solveLineCircleIntersect(lineEquation, center, radius, solutions);
  // Find which solutions sits between A and B
  double angle = getAngle(
    unit, sf::Vector2f(solutions[0].x - pivot.x, solutions[0].y - pivot.y)
  );
  sf::Vector2f solution;
  if ((angle < 1 && inA) || (angle > 1 && inB)) {
    solution = solutions[0];
  } else {
    solution = solutions[1];
  }
  return getDistance(pivot, solution)/length;
}

void SmallCut::draw(sf::RenderWindow *window) {
  sf::VertexArray cut(sf::LineStrip, 2);
  cut[0].position = positionA;
  cut[1].position = positionB;
  cut[0].color = sf::Color(200, 0, 0);
  cut[1].color = sf::Color(200, 0, 0);
  window->draw(cut);
}

SmallCut::SmallCut(
  GlobalValues *global, const sf::Vector2i &pos, double angle
) : CommonObject(global) {
  unit = unitAtAngle(angle);
  positionA = sf::Vector2f(pos.x, pos.y);
  positionB = positionA + (unit*length);
  // Compute line equation from positions [ax+by=1]
  // Special case for angle = 0 or 180 deg
  if (angle == 0 || angle == M_PI) {
    lineEquation[0] = 0;
    lineEquation[1] = 1/(positionB.y);
    return;
  }
  // a = (y2-y1) / (x1y2 - x2y1)
  lineEquation[0] = (
    (positionB.y-positionA.y) /
    (positionA.x*positionB.y - positionB.x*positionA.y)
  );
  // b = a * (x1 - x2) / (y2 - y1)
  lineEquation[1] = (
    lineEquation[0] * (positionA.x - positionB.x) / (positionB.y - positionA.y)
  );
}
