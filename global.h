#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>

class GlobalValues {
  private:
    sf::Clock clock;
    sf::Vector2i mousePos;

    bool focus = true;
    bool shouldUpdateMouse = true;
    bool isMouseActive = false;
    bool isKeyUp = false;
    bool isKeyLeft = false;
    bool isKeyDown = false;
    bool isKeyRight = false;
    bool isKeySpecial = false;
    double elapsedTime = 0;

  public:
    sf::Time restartTime() { return clock.restart(); } // only main should call this

    bool updateMouse() { return shouldUpdateMouse; }
    bool hasFocus() { return focus; }
    bool getKeyUp() { return isKeyUp; }
    bool getKeyDown() { return isKeyDown; }
    bool getKeyLeft() { return isKeyLeft; }
    bool getKeyRight() { return isKeyRight; }
    bool getKeySpecial() { return isKeySpecial; }
    bool getMouseActive() { return isMouseActive; }
    double getElapsedTime() { return elapsedTime; }
    const sf::Vector2i & getMousePos() { return mousePos; }

    void setFocus(bool f) { focus = f; }
    void setUpdateMouse(bool u) { shouldUpdateMouse = u; }
    void setMouseActive(bool a) { isMouseActive = a; }
    void setKeyUp(bool u) { isKeyUp = u; }
    void setKeyDown(bool d) { isKeyDown = d; }
    void setKeyLeft(bool l) { isKeyLeft = l; }
    void setKeyRight(bool r) { isKeyRight = r; }
    void setKeySpecial(bool s) { isKeySpecial = s; }
    void setMousePos(const sf::Vector2i &pos) { mousePos = pos; }
    void setElapsedTime(double t) { elapsedTime = t; }

    GlobalValues() {}
    ~GlobalValues() {}
};

#endif
