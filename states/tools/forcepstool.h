#ifndef STATE_FORCEPSTOOL_H
#define STATE_FORCEPSTOOL_H

#include <SFML/Graphics.hpp>

#include "../enemy/common.h"
#include "commontool.h"

#include "math.h"

class ForcepsToolState: public CommonToolState {
  private:
    bool lastMouseActive = false;
    CommonEnemyState *heldItem = NULL;

  public:
    ForcepsToolState(GlobalValues *g, CommonPatientState *p) : CommonToolState(g, p) {}
    ~ForcepsToolState();

    void deselect();
    void update(bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
