#include "freeformline.h"

void FreeFormLineObject::addPoint() {
  sf::Vector2i current = global->getMousePos();
  if (current.x != last.x && current.y != last.y) {
    positions.push_back(current);
    last = current;
  }
}

void FreeFormLineObject::addPointTwice() {
  sf::Vector2i current = global->getMousePos();
  if (current.x != last.x && current.y != last.y) {
    positions.push_back(current);
    positions.push_back(current);
    last = current;
  }
}

void FreeFormLineObject::replacePoint() {
  sf::Vector2i current = global->getMousePos();
  positions[positions.size()-1] = current;
  last = current;
}

void FreeFormLineObject::replaceAndAddDuplicate() {
  sf::Vector2i current = global->getMousePos();
  positions[positions.size()-1] = current;
  positions.push_back(current);
  last = current;
}

void FreeFormLineObject::draw(sf::RenderWindow *window) {
  if (positions.size() < 2) return;
  sf::VertexArray form(sf::LineStrip, positions.size());
  for (unsigned long i = 0; i < positions.size(); i++) {
    form[i].position = sf::Vector2f(positions[i].x, positions[i].y);
    form[i].color = color;
  }
  window->draw(form);
}
