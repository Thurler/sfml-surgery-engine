#ifndef OBJ_RIPPLE_H
#define OBJ_RIPPLE_H

#include <SFML/Graphics.hpp>

#include "common.h"

class RippleProperties {
  public:
    RippleProperties() {}
    virtual ~RippleProperties() {}
};

class Ripple: public CommonObject {
  private:

    sf::Vector2i center;
    sf::Color color;
    double timer = 0;
    double duration;
    double expansion;
    unsigned int radius;
    unsigned int growthRadius;
    bool expired = false;
    RippleProperties *properties;

  public:
    Ripple(
      GlobalValues *g, const sf::Vector2i &c, sf::Color cl, double d, double e,
      int r, int gr, RippleProperties *p
    ) :
      center(c), color(cl), duration(d), expansion(e), radius(r),
      growthRadius(gr), properties(p), CommonObject(g) {}
    ~Ripple() {}

    unsigned int effectiveRadius();
    bool hasExpired() { return expired; }
    sf::Vector2i getCenter() { return center; }
    RippleProperties * getProperties() { return properties; }
    void update(const sf::Time &t);
    void draw(sf::RenderWindow *w);
};

#endif
