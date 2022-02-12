#include "forcepstool.h"
#include "math.h"

const sf::Vector2i ForcepsToolState::trayPosition = sf::Vector2i(1290, 290);

bool ForcepsToolState::insideTray(const sf::Vector2i &position) {
  double radiusX = trayRadius * trayEllipseScale;
  double radiusY = trayRadius;
  double centerX = trayPosition.x;
  double centerY = trayPosition.y;
  double horizontalDisp = pow(position.x - centerX, 2) / pow(radiusX, 2);
  double verticalDisp = pow(position.y - centerY, 2) / pow(radiusY, 2);
  return horizontalDisp + verticalDisp <= 1;
}

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
      if (!heldItem->updateForceps(position)) {
        heldItem->releaseForceps(insideTray(position));
        heldItem = NULL;
      }
    }
  } else if (!isMouseActive && lastMouseActive) {
    // no longer holding something
    if (heldItem != NULL) {
      heldItem->releaseForceps(insideTray(position));
      heldItem = NULL;
    }
  }
  lastMouseActive = isMouseActive;
}

void ForcepsToolState::draw(sf::RenderWindow *window, bool active) {
  // draw the tray, but only if it's the active tool and holding something
  if (active && heldItem != NULL) {
    sf::CircleShape tray(trayRadius);
    tray.setFillColor(sf::Color(255, 255, 255, 128));
    tray.setScale(trayEllipseScale, 1);
    double radiusX = trayRadius * trayEllipseScale;
    double radiusY = trayRadius;
    tray.setPosition(trayPosition.x - radiusX, trayPosition.y - radiusY);
    window->draw(tray);
  }
}

void ForcepsToolState::deselect() {
  lastMouseActive = false;
  if (heldItem != NULL) {
    sf::Vector2i position = global->getMousePos();
    heldItem->releaseForceps(insideTray(position));
    heldItem = NULL;
  }
}

ForcepsToolState::~ForcepsToolState() {
  deselect();
}
