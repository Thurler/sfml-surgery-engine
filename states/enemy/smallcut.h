#ifndef STATE_SMALLCUTENEMY_H
#define STATE_SMALLCUTENEMY_H

#include "../../objects/ripple.h"
#include "../../objects/smallcut.h"
#include "common.h"

class SmallCutState: public CommonEnemyState {
  private:
    static constexpr double timeToHeal = 0.1;
    static constexpr double maxHP = 100;

    double damagePerSec() { return 0.1; }
    double permDamagePerSec() { return 0.02; }
    unsigned int scoreValue() { return 50; }

    SmallCut *cut = NULL;
    CommonEnemyState *appended = NULL;
    double hp = 100;

  public:
    SmallCutState(
        GlobalValues *g, const sf::Vector2i &p, double a, CommonEnemyState *o = NULL
    );
    ~SmallCutState();

    bool isDead() { return hp <= 0; }
    void removeAppended() { appended = NULL; }
    void interactGelRipple(Ripple *ripple);

    void update() {}
    void draw(sf::RenderWindow *w);
};

#endif
