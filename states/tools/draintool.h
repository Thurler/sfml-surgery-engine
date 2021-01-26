#ifndef STATE_DRAINTOOL_H
#define STATE_DRAINTOOL_H

#include <SFML/Graphics.hpp>

#include "commontool.h"

class DrainToolState: public CommonToolState {
  private:
    static constexpr int width = 8;

    void processDrain();

  public:
    DrainToolState(GlobalValues *g, VitalsState *v) : CommonToolState(g, v) {}
    ~DrainToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
