#ifndef OBJ_POINTER_H
#define OBJ_POINTER_H

#include <SFML/Graphics.hpp>

#include "common.h"

class PointerObject: public CommonObject {
  private:
    static constexpr double radius = 5.0f;
    sf::Vector2i position;
  public:
    PointerObject(GlobalValues *g) : CommonObject(g) {}
    ~PointerObject() {}

    void update(const sf::Time &t);
    void draw(sf::RenderWindow *w);
};

#endif
