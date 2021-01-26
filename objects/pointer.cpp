#include "pointer.h"

void PointerObject::update(const sf::Time &time) {
  position = global->getMousePos();
}

void PointerObject::draw(sf::RenderWindow *window) {
  sf::CircleShape pointer(radius);
  pointer.setFillColor(sf::Color::White);
  sf::FloatRect bounds = pointer.getLocalBounds();
  pointer.setPosition(
    position.x - (bounds.width/2),
    position.y - (bounds.height/2)
  );
  window->draw(pointer);
}
