#ifndef STATE_ULTRASOUNDTOOL_H
#define STATE_ULTRASOUNDTOOL_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../objects/ripple.h"
#include "commontool.h"

class UltrasoundToolState: public CommonToolState {
  private:
    static constexpr double cooldown = 0.4;
    std::vector<Ripple *> ripples;
    bool lastMouseActive = false;
    double timer = 0;

    void initRipple();
    void updateRipples(const sf::Time &t);

  public:
    UltrasoundToolState(GlobalValues *g, CommonPatientState *p) : CommonToolState(g, p) {}
    ~UltrasoundToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
