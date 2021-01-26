#ifndef OBJ_MOUSETEXT_H
#define OBJ_MOUSETEXT_H

#include <SFML/Graphics.hpp>

#include "text.h"

class MouseTextObject: public TextObject {
  public:
    MouseTextObject(GlobalValues *g) :  
      TextObject(g, sf::Vector2i(1275, 715), sf::Color::White, 10) {}
    ~MouseTextObject() {}

    void update(const sf::Time &t);
};

#endif
