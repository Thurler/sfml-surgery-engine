#include "text.h"

void TextObject::draw(sf::RenderWindow *window) {
  if (content == "") return;
  sf::Text text;
  text.setFont(font);
  text.setString(content);
  text.setCharacterSize(size);
  text.setFillColor(color);
  text.setStyle(sf::Text::Bold);
  sf::FloatRect bounds = text.getLocalBounds();
  text.setPosition(position.x - bounds.width, position.y - bounds.height);
  window->draw(text);
}
