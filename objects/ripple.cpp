#include "ripple.h"

unsigned int Ripple::effectiveRadius() {
  return radius + std::min(1.0, timer/expansion)*growthRadius;
}

void Ripple::update(const sf::Time &time) {
  timer += time.asMicroseconds() / 1000000.0f;
  if (timer > duration) {
    expired = true;
  }
}

void Ripple::draw(sf::RenderWindow *window) {
  int effRadius = effectiveRadius();
  sf::CircleShape ripple(effRadius);
  ripple.setFillColor(color);
  ripple.setPosition(center.x - effRadius, center.y - effRadius);
  window->draw(ripple);
}
