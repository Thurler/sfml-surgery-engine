#ifndef OBJ_FPSTEXT_H
#define OBJ_FPSTEXT_H

#include <SFML/Graphics.hpp>

#include "text.h"

class FPSTextObject: public TextObject {
  private:
    static constexpr unsigned int limit = 30;
    unsigned int lastValues[limit] = {0};
    unsigned int index = 0;
  public:
    FPSTextObject(GlobalValues *g) :
      TextObject(g, sf::Vector2i(1275, 700), sf::Color::White, 10) {}
    ~FPSTextObject() {}

    void update(const sf::Time &t);
};

#endif
