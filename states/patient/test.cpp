#include "../tools/geltool.h"
#include "../enemy/glass.h"
#include "test.h"

#include "math.h"

const sf::Vector2i TestPatientState::smallCutsPositions[smallCutCount] = {
  sf::Vector2i(100, 200),
  sf::Vector2i(200, 400),
  sf::Vector2i(500, 300),
  sf::Vector2i(400, 200),
  sf::Vector2i(600, 500),
  sf::Vector2i(300, 300),
};

const double TestPatientState::smallCutsAngles[smallCutCount] = {
  0,
  M_PI / 2,
  M_PI / 4,
  M_PI / 3,
  M_PI / 12,
  M_PI,
};

void TestPatientState::interactStabilizer(double healed) {
  vitals->receiveHeal(healed);
}

void TestPatientState::interactGel(const std::vector<Ripple *> &ripples, double healed) {
  for (unsigned long i = 0; i < ripples.size(); i++) {
    bool isSmall = dynamic_cast<GelProperties *>(ripples[i]->getProperties())->isSmall();
    if (!isSmall) {
      vitals->receiveHeal(healed);
    }
    for (unsigned int j = 0; j < smallCutCount; j++) {
      if (smallCuts[j] == NULL || smallCuts[j]->isDead()) continue;
      smallCuts[j]->interactGelRipple(ripples[i]);
    }
  }
}

CommonEnemyState *TestPatientState::interactForceps(const sf::Vector2i &position) {
  for (unsigned int i = 0; i < smallCutCount; i++) {
    if (glassShards[i] == NULL || glassShards[i]->isDisposed()) continue;
    if (glassShards[i]->grabForceps(position)) {
      return glassShards[i];
    }
  }
  return NULL;
}

void TestPatientState::update() {
  for (unsigned int i = 0; i < smallCutCount; i++) {
    if (smallCuts[i] == NULL) continue;
    if (smallCuts[i]->isDead()) {
      smallCuts[i]->applyScore(score);
      delete smallCuts[i];
      smallCuts[i] = NULL;
      continue;
    }
    smallCuts[i]->applyDamage(vitals);
    if (glassShards[i] == NULL) continue;
    if (glassShards[i]->isDisposed()) {
      glassShards[i]->applyScore(score);
      delete glassShards[i];
      glassShards[i] = NULL;
      smallCuts[i]->removeAppended();
      continue;
    }
    if (glassShards[i]->checkAndResetDropped()) {
      glassShards[i]->applyFlatDamage(vitals);
    }
  }
}

void TestPatientState::draw(sf::RenderWindow *window) {
  for (unsigned int i = 0; i < smallCutCount; i++) {
    if (smallCuts[i] == NULL) continue;
    smallCuts[i]->draw(window);
  }
}

TestPatientState::TestPatientState(
  GlobalValues *global, VitalsState *vitals, ScoreState *score
) : CommonPatientState(global, vitals, score) {
  for (unsigned int i = 0; i < smallCutCount; i++) {
    GlassShardState *shard = new GlassShardState(
      global, smallCutsPositions[i], smallCutsAngles[i]
    );
    glassShards[i] = shard;
    smallCuts[i] = new SmallCutState(
      global, smallCutsPositions[i], smallCutsAngles[i], shard
    );
  }
}

TestPatientState::~TestPatientState() {
  for (unsigned int i = 0; i < smallCutCount; i++) {
    if (smallCuts[i] == NULL) continue;
    delete smallCuts[i];
  }
}
