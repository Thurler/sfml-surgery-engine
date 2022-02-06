#include <string>
#include "mousetext.h"

void MouseTextObject::update() {
  sf::Vector2i pos = global->getMousePos();
  setContent(std::to_string(pos.x) + ", " + std::to_string(pos.y));
}
