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

    SmallCut *cut = NULL;
    double hp = 100;

  public:
    SmallCutState(GlobalValues *g, const sf::Vector2i &p, double a);
    ~SmallCutState();

    bool isDead() { return hp <= 0; }
    void interactGelRipple(Ripple *ripple);

    void update(const sf::Time &t) {}
    void draw(sf::RenderWindow *w);
};

#endif
