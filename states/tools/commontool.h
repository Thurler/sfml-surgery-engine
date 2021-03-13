#ifndef STATE_COMMONTOOL_H
#define STATE_COMMONTOOL_H

#include "../patient/common.h"
#include "../common.h"

class CommonToolState: public CommonState {
  protected:
    CommonPatientState *patient;
    CommonToolState(GlobalValues *g, CommonPatientState *p) : patient(p), CommonState(g) {}
  public:
    virtual ~CommonToolState() {}
    virtual void deselect() = 0;
    virtual void update(const sf::Time &t, bool active) = 0;
    virtual void draw(sf::RenderWindow *w, bool active) = 0;
    void update(const sf::Time &t) { update(t, true); }
    void draw(sf::RenderWindow *w) { draw(w, true); }
};

#endif
