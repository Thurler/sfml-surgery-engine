#include "smallcut.h"

void SmallCutState::interactGelRipple(Ripple *ripple) {
  double elapsed = global->getElapsedTime();
  double collision = cut->collide(ripple);
  hp -= maxHP*collision*elapsed/timeToHeal;
}

void SmallCutState::draw(sf::RenderWindow *window) {
  cut->draw(window);
}

SmallCutState::SmallCutState(
  GlobalValues *global, const sf::Vector2i &position, double angle
) : CommonEnemyState(global) {
  cut = new SmallCut(global, position, angle);
}

SmallCutState::~SmallCutState() {
  if (cut != NULL) {
    delete cut;
  }
}
