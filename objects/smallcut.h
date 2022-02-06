#ifndef OBJ_SMALLCUT_H
#define OBJ_SMALLCUT_H

#include <SFML/Graphics.hpp>

#include "ripple.h"
#include "common.h"

class SmallCut: public CommonObject {
  private:
    static constexpr float length = 50;

    sf::Vector2f positionA;
    sf::Vector2f positionB;
    sf::Vector2f unit;
    double lineEquation[2];

  public:
    SmallCut(GlobalValues *g, const sf::Vector2i &p, double a);
    ~SmallCut() {}

    double collide(Ripple *ripple);

    void update() {}
    void draw(sf::RenderWindow *w);
};

#endif
