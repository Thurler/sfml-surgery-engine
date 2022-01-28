#include "text.h"

void TextObject::draw(sf::RenderWindow *window) {
  if (content == "") return;
  text.setString(content);
  text.setCharacterSize(size);
  text.setFillColor(color);
  sf::FloatRect bounds = text.getLocalBounds();
  text.setPosition(position.x - bounds.width, position.y - bounds.height);
  window->draw(text);
}
