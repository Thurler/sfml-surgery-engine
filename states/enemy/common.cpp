#include "common.h"

void CommonEnemyState::applyDamage(VitalsState *vitals) {
  double elapsed = global->getElapsedTime();
  vitals->receiveDamage(elapsed * damagePerSec());
  vitals->receivePermDamage(elapsed * permDamagePerSec());
}
