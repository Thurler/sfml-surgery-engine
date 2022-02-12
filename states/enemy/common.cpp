#include "common.h"

void CommonEnemyState::applyFlatDamage(VitalsState *vitals) {
  vitals->receiveDamage(flatDamage());
  vitals->receivePermDamage(flatPermDamage());
}

void CommonEnemyState::applyDamage(VitalsState *vitals) {
  double elapsed = global->getElapsedTime();
  vitals->receiveDamage(elapsed * damagePerSec());
  vitals->receivePermDamage(elapsed * permDamagePerSec());
}
