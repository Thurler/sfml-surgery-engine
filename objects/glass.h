#ifndef OBJ_GLASS_H
#define OBJ_GLASS_H

#include <SFML/Graphics.hpp>

#include "common.h"

class GlassShard: public CommonObject {
  private:
    static constexpr float width = 25;
    static constexpr float height = 50;

    bool removed = false;
    sf::Vector2f basePosition;  // top left corner
    sf::Vector2f position;
    sf::Vector2f positionA;  // underlying cut
    sf::Vector2f positionB;
    sf::Vector2f unit;
    sf::Vector2f unitCut;
    float offset;

    float getEffectiveHeight();

  public:
    GlassShard(GlobalValues *g, const sf::Vector2i &p, double a);
    ~GlassShard() {}

    const sf::Vector2f & getBasePosition() { return basePosition; }
    void setRemoved(bool r) { removed = r; }
    void resetPosition() { position = basePosition; }
    void setPosition(const sf::Vector2i &p) { position = sf::Vector2f(p.x, p.y); }
    bool checkCollision(const sf::Vector2i &p);
    bool checkMistake();
    bool checkRemoved();
    double getExitAngleFactor();

    void update() {}
    void draw(sf::RenderWindow *w);
};

#endif
