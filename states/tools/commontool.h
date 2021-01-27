#ifndef STATE_COMMONTOOL_H
#define STATE_COMMONTOOL_H

#include "../score.h"
#include "../vitals.h"
#include "../common.h"

class CommonToolState: public CommonState {
  protected:
    ScoreState *score;
    VitalsState *vitals;
    CommonToolState(GlobalValues *g, VitalsState *v, ScoreState *s) :
      vitals(v), score(s), CommonState(g) {}
  public:
    virtual ~CommonToolState() {}
    virtual void deselect() = 0;
    virtual void update(const sf::Time &t, bool active) = 0;
    virtual void draw(sf::RenderWindow *w, bool active) = 0;
    void update(const sf::Time &t) { update(t, true); }
    void draw(sf::RenderWindow *w) { draw(w, true); }
};

#endif
