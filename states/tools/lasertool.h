#ifndef STATE_LASERTOOL_H
#define STATE_LASERTOOL_H

#include <SFML/Graphics.hpp>

#include "math.h"
#include "commontool.h"

class LaserToolState: public CommonToolState {
  private:
    static constexpr int width = 8;
    static constexpr double slope = M_PI / 3;

    void processLaser();

  public:
    LaserToolState(GlobalValues *g, CommonPatientState *p) : CommonToolState(g, p) {}
    ~LaserToolState();

    void deselect();
    void update(bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
