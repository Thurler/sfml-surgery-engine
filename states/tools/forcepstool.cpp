#include "forcepstool.h"

void ForcepsToolState::update(bool active) {
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  sf::Vector2i position = global->getMousePos();
  if (isMouseActive && !lastMouseActive) {
    // now attempting to grab something
    CommonEnemyState *held = patient->interactForceps(position);
    if (held != NULL) {
      heldItem = held;
    }
  } else if (isMouseActive && lastMouseActive) {
    // still holding something, update position
    if (heldItem != NULL) {
      heldItem->updateForceps(position);
    }
  } else if (!isMouseActive && lastMouseActive) {
    // no longer holding something
    if (heldItem != NULL) {
      heldItem->releaseForceps();
      heldItem = NULL;
    }
  }
  lastMouseActive = isMouseActive;
}

void ForcepsToolState::draw(sf::RenderWindow *window, bool active) {
}

void ForcepsToolState::deselect() {
  lastMouseActive = false;
  if (heldItem != NULL) {
    heldItem->releaseForceps();
    heldItem = NULL;
  }
}

ForcepsToolState::~ForcepsToolState() {
  deselect();
}
