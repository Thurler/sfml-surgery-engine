#ifndef OBJ_GLASS_H
#define OBJ_GLASS_H

#include <SFML/Graphics.hpp>

#include "common.h"

class GlassShard: public CommonObject {
  private:
    static constexpr float width = 30;
    static constexpr float height = 60;

    bool removed = false;
    sf::Vector2f basePosition;  // top left corner
    sf::Vector2f position;
    sf::Vector2f positionA;  // underlying cut
    sf::Vector2f positionB;
    sf::Vector2f unit;
    sf::Vector2f unitCut;

    float getEffectiveHeight();

  public:
    GlassShard(GlobalValues *g, const sf::Vector2i &p, double a);
    ~GlassShard() {}

    const sf::Vector2f & getBasePosition() { return basePosition; }
    void setRemoved(bool r) { removed = r; }
    void resetPosition() { position = basePosition; }
    void setPosition(const sf::Vector2i &p) { position = sf::Vector2f(p.x, p.y); }
    bool checkCollision(const sf::Vector2i &p);

    void update() {}
    void draw(sf::RenderWindow *w);
};

#endif
