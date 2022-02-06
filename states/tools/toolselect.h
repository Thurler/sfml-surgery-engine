#ifndef STATE_TOOLSELECT_H
#define STATE_TOOLSELECT_H

#include <SFML/Graphics.hpp>

#include "../score.h"
#include "../vitals.h"
#include "commontool.h"

enum Tool {
    Suture = 0,
    Drain,
    Laser,
    Ultrasound,
    Scalpel,
    Forceps,
    Gel,
    Syringe,
    HealingTouch
};

class ToolSelectState: public CommonState {
  private:
    static const unsigned int toolCount = 9;
    static const unsigned int wheelRadius = 50;
    static const unsigned int toolRadius = 10;
    static const sf::Vector2i toolPosition;

    unsigned int diagonalRelease = 0;
    bool lastKeyUp = false;
    bool lastKeyDown = false;
    bool lastKeyLeft = false;
    bool lastKeyRight = false;
    bool lastKeySpecial = false;
    CommonToolState *currentTool = NULL;
    CommonToolState *tools[toolCount] = {NULL};

  public:
    ToolSelectState(GlobalValues *g, CommonPatientState *p);
    ~ToolSelectState();

    void update();
    void draw(sf::RenderWindow *w);
};

#endif
