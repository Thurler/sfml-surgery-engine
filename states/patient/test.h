#ifndef STATE_TESTPATIENT_H
#define STATE_TESTPATIENT_H

#include "common.h"

class TestPatientState: public CommonPatientState {
  public:
    TestPatientState(GlobalValues *g, VitalsState *v, ScoreState *s) : CommonPatientState(g, v, s) {}
    ~TestPatientState() {}

    void update(const sf::Time &t) {}
    void draw(sf::RenderWindow *w) {}

    void interactGel(const std::vector<Ripple *> &ripples, double healed);
    void interactSuture() {}
    void interactUltrasound() {}
    void interactLaser() {}
    void interactDrain() {}
    void interactScalpel() {}
    void interactForceps() {}
    void interactStabilizer(double healed);
};

#endif
