#ifndef STATE_TESTPATIENT_H
#define STATE_TESTPATIENT_H

#include <SFML/Graphics.hpp>

#include "../enemy/smallcut.h"
#include "common.h"

class TestPatientState: public CommonPatientState {
  private:
    static constexpr unsigned int smallCutCount = 6;
    static const sf::Vector2i smallCutsPositions[smallCutCount];
    static const double smallCutsAngles[smallCutCount];

    SmallCutState *smallCuts[smallCutCount];

  public:
    TestPatientState(GlobalValues *g, VitalsState *v, ScoreState *s);
    ~TestPatientState();

    void update(const sf::Time &t);
    void draw(sf::RenderWindow *w);

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
