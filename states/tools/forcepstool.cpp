#include "forcepstool.h"

void ForcepsToolState::processForceps() {
}

void ForcepsToolState::update(bool active) {
  processForceps();
}

void ForcepsToolState::draw(sf::RenderWindow *window, bool active) {
}

void ForcepsToolState::deselect() {
}

ForcepsToolState::~ForcepsToolState() {
  deselect();
}
