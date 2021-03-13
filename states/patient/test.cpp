#include "../tools/geltool.h"
#include "test.h"

void TestPatientState::interactStabilizer(double healed) {
  vitals->receiveHeal(healed);
}

void TestPatientState::interactGel(const std::vector<Ripple *> &ripples, double healed) {
  for (unsigned long i = 0; i < ripples.size(); i++) {
    bool isSmall = dynamic_cast<GelProperties *>(ripples[i]->getProperties())->isSmall();
    if (!isSmall) {
      vitals->receiveHeal(healed);
    }
  }
}
