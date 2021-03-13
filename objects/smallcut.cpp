#include "smallcut.h"

unsigned int SmallCut::collide(Ripple *ripple) {
  double distA = getDistance(positionA, ripple->getCenter());
  double distB = getDistance(positionB, ripple->getCenter());
  unsigned int radius = ripple->effectiveRadius();
  return (distA <= radius) + (distB <= radius);
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
  sf::Vector2f unit = unitAtAngle(angle);
  positionA = sf::Vector2f(pos.x, pos.y);
  positionB = positionA + (unit*length);
}
