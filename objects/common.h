#ifndef OBJ_COMMON_H
#define OBJ_COMMON_H

#include <SFML/Graphics.hpp>
#include "../global.h"

class CommonObject {
  protected:
    GlobalValues *global = NULL;

    CommonObject(GlobalValues *g) : global(g) {}
    ~CommonObject() {}

    sf::Vector2f unitAtAngle(double angle);
    double getDistance(sf::Vector2i a, sf::Vector2i b);
    double getDistance(sf::Vector2f a, sf::Vector2i b);
    double getAngle(sf::Vector2i a, sf::Vector2i b);
    std::string padIntToString(long s, unsigned int sz, char p);

  public:
    virtual void update(const sf::Time &t) = 0;
    virtual void draw(sf::RenderWindow *w) = 0;
};

#endif
