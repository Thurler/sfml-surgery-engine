#include "ripple.h"

void Ripple::update(const sf::Time &time) {
  timer += time.asMicroseconds() / 1000000.0f;
  if (timer > duration) {
    expired = true;
  }
}

void Ripple::draw(sf::RenderWindow *window) {
  int effectiveRadius = radius + std::min(1.0, timer/expansion)*growthRadius;
  sf::CircleShape ripple(effectiveRadius);
  ripple.setFillColor(color);
  ripple.setPosition(center.x - effectiveRadius, center.y - effectiveRadius);
  window->draw(ripple);
}
