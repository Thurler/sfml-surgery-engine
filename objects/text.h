#ifndef OBJ_TEXT_H
#define OBJ_TEXT_H

#include <SFML/Graphics.hpp>
#include <string>

#include "common.h"

class TextObject: public CommonObject {
  protected:
    std::string content = "";
    sf::Vector2i position;
    sf::Font font;
    sf::Color color;
    unsigned int size;

  public:
    TextObject(GlobalValues *g, const sf::Vector2i &p, sf::Color c, unsigned int s) :
    position(p), color(c), size(s), CommonObject(g) {
      font.loadFromFile("C:/Windows/Fonts/meiryo.ttc");
    }
    ~TextObject() {}

    virtual void update(const sf::Time &t) {}
    virtual void draw(sf::RenderWindow *w);
    void setContent(const std::string &c) { content = c; }
    void setColor(const sf::Color &c) { color = c; }
};

#endif
