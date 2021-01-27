#ifndef STATE_GELTOOL_H
#define STATE_GELTOOL_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "../../objects/ripple.h"
#include "commontool.h"

class GelProperties: public RippleProperties {
  private:
    bool small;
  public:
    GelProperties(bool s) : small(s) {}
    ~GelProperties() {}

    bool isSmall() {  return small; }
};

class GelToolState: public CommonToolState {
  private:
    static constexpr double cooldown = 0.1;
    static constexpr double duration = 1.5;
    static constexpr unsigned int radius = 20;
    static constexpr double fullHeal = 0.2;
    std::vector<Ripple *> ripples;
    sf::Vector2i lastCenter;
    double timer = 0;

    void initRipple(bool small);
    void updateRipples(const sf::Time &t);

  public:
    GelToolState(GlobalValues *g, VitalsState *v, ScoreState *s) : CommonToolState(g, v, s) {}
    ~GelToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
