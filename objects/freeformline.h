#ifndef OBJ_FREEFORMLINE_H
#define OBJ_FREEFORMLINE_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "common.h"

class FreeFormLineObject: public CommonObject {
  private:
    sf::Vector2i last = sf::Vector2i(0, 0);
    sf::Color color;
    std::vector<sf::Vector2i> positions;
  public:
    FreeFormLineObject(GlobalValues *g, sf::Color c) :
      color(c), CommonObject(g) { positions.reserve(100); }
    ~FreeFormLineObject() {}

    void addPoint();
    void addPointTwice();
    void replacePoint();
    void replaceAndAddDuplicate();
    void update(const sf::Time &t) {}
    void draw(sf::RenderWindow *w);
};

#endif
