#include "../tools/geltool.h"
#include "test.h"

#include "math.h"

const sf::Vector2i TestPatientState::smallCutsPositions[smallCutCount] = {
  sf::Vector2i(100, 200), sf::Vector2i(200, 400), sf::Vector2i(500, 300)
};

const double TestPatientState::smallCutsAngles[smallCutCount] = {
  0, M_PI / 2, M_PI / 4
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

void TestPatientState::update(const sf::Time &time) {
  for (unsigned int i = 0; i < smallCutCount; i++) {
    if (smallCuts[i] == NULL) continue;
    if (smallCuts[i]->isDead()) {
      delete smallCuts[i];
      smallCuts[i] = NULL;
      score->receiveScore(50);
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
    smallCuts[i] = new SmallCutState(global, smallCutsPositions[i], smallCutsAngles[i]);
  }
}

TestPatientState::~TestPatientState() {
  for (unsigned int i = 0; i < smallCutCount; i++) {
    if (smallCuts[i] == NULL) continue;
    delete smallCuts[i];
  }
}
