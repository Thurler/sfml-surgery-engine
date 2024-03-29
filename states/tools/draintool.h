#ifndef STATE_DRAINTOOL_H
#define STATE_DRAINTOOL_H

#include <SFML/Graphics.hpp>

#include "commontool.h"

class DrainToolState: public CommonToolState {
  private:
    static constexpr int width = 8;

    void processDrain();

  public:
    DrainToolState(GlobalValues *g, CommonPatientState *p) : CommonToolState(g, p) {}
    ~DrainToolState();

    void deselect();
    void update(bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
