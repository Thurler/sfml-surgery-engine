#ifndef STATE_COMMONENEMY_H
#define STATE_COMMONENEMY_H

#include "../common.h"
#include "../vitals.h"
#include "../score.h"

enum ScoreGrade {
  Bad = 0,
  Good,
  Cool
};

class CommonEnemyState: public CommonState {
  protected:
    CommonEnemyState(GlobalValues *g) : CommonState(g) {}

    virtual double damagePerSec() { return 0; }
    virtual double permDamagePerSec() { return 0; }
    virtual unsigned int scoreValue() { return 0; }

  public:
    virtual ~CommonEnemyState() {}

    virtual void updateForceps(const sf::Vector2i &p) {}
    virtual void releaseForceps() {}
    virtual void applyDamage(VitalsState *v);
    void applyScore(ScoreState *s) { s->receiveScore(scoreValue()); }
};

#endif
