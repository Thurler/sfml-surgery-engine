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
    LaserToolState(GlobalValues *g, VitalsState *v, ScoreState *s) : CommonToolState(g, v, s) {}
    ~LaserToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
