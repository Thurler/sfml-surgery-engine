#ifndef STATE_FORCEPSTOOL_H
#define STATE_FORCEPSTOOL_H

#include <SFML/Graphics.hpp>

#include "math.h"
#include "commontool.h"

class ForcepsToolState: public CommonToolState {
  private:
    void processForceps();

  public:
    ForcepsToolState(GlobalValues *g, VitalsState *v) : CommonToolState(g, v) {}
    ~ForcepsToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
