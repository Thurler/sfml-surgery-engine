#include "smallcut.h"

void SmallCutState::interactGelRipple(Ripple *ripple) {
  if (appended) return;
  double elapsed = global->getElapsedTime();
  double collision = cut->collide(ripple);
  hp -= maxHP * collision * (elapsed / timeToHeal);
}

void SmallCutState::draw(sf::RenderWindow *window) {
  cut->draw(window);
  if (appended) {
    appended->draw(window);
  }
}

SmallCutState::SmallCutState(
  GlobalValues *global, const sf::Vector2i &position, double angle, CommonEnemyState *other
) : CommonEnemyState(global) {
  cut = new SmallCut(global, position, angle);
  if (other) {
    appended = other;
  }
}

SmallCutState::~SmallCutState() {
  if (cut != NULL) {
    delete cut;
  }
  if (appended != NULL) {
    delete appended;
  }
}
