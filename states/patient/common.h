#ifndef STATE_COMMONPATIENT_H
#define STATE_COMMONPATIENT_H

#include "../../objects/ripple.h"
#include "../enemy/common.h"
#include "../common.h"
#include "../score.h"
#include "../vitals.h"

class CommonPatientState: public CommonState {
  protected:
    ScoreState *score = NULL;
    VitalsState *vitals = NULL;

    CommonPatientState(
      GlobalValues *g, VitalsState *v, ScoreState *s
    ) : vitals(v), score(s), CommonState(g) {}

  public:
    virtual ~CommonPatientState() {}

    virtual void interactGel(const std::vector<Ripple *> &ripples, double healed) = 0;
    virtual void interactSuture() = 0;
    virtual void interactUltrasound() = 0;
    virtual void interactLaser() = 0;
    virtual void interactDrain() = 0;
    virtual void interactScalpel() = 0;
    virtual CommonEnemyState *interactForceps(const sf::Vector2i &p) = 0;
    virtual void interactStabilizer(double healed) = 0;
};

#endif
