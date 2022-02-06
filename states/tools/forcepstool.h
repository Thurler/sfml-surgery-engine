#ifndef STATE_FORCEPSTOOL_H
#define STATE_FORCEPSTOOL_H

#include <SFML/Graphics.hpp>

#include "math.h"
#include "commontool.h"

class ForcepsToolState: public CommonToolState {
  private:
    void processForceps();

  public:
    ForcepsToolState(GlobalValues *g, CommonPatientState *p) : CommonToolState(g, p) {}
    ~ForcepsToolState();

    void deselect();
    void update(bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
