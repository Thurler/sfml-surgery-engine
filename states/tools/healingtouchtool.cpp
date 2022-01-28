#include "healingtouchtool.h"

void HealingTouchToolState::initStar() {
  starLineObject = new FreeFormLineObject(global, sf::Color::Cyan);
  starLineObject->addPointTwice();
  basePivot = global->getMousePos();
}

void HealingTouchToolState::destroyStar() {
  hasBaseVector = false;
  delete starLineObject;
  starLineObject = NULL;
}

void HealingTouchToolState::processStar() {
  sf::Vector2i currentPos = global->getMousePos();
  if (!hasBaseVector && getDistance(currentPos, basePivot) >= basePivotDistance) {
    // cursor beyond pivot range, lock vector
    iterVector = sf::Vector2i(currentPos.x - basePivot.x, currentPos.y - basePivot.y);
    iterPivot = currentPos;
    hasBaseVector = true;
  } else if (hasBaseVector) {
    // compare current distance with iterative pivot
    if (getDistance(currentPos, iterPivot) >= iterPivotDistance) {
      // compute small distance vector
      sf::Vector2i curIterVector = sf::Vector2i(currentPos.x - iterPivot.x, currentPos.y - iterPivot.y);
      // check for sudden angle change
      double iterAngle = getAngle(curIterVector, iterVector);
      if (iterAngle > iterAngleTolerance) {
        // sudden change, lock suture segment
        basePivot = currentPos;
        starLineObject->replaceAndAddDuplicate();
        hasBaseVector = false;
        return;
      } else {
        // iterate pivot to where we are now
        iterPivot = currentPos;
        iterVector = curIterVector;
      }
    }
  }
  starLineObject->replacePoint();
}

void HealingTouchToolState::update(const sf::Time &t, bool active) {
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  if (lastMouseActive && isMouseActive) {
    // mouse is still active
    processStar();
  } else if (lastMouseActive) {
    // mouse is no longer active
    destroyStar();
  } else if (isMouseActive) {
    // mouse is now active
    initStar();
  }
  lastMouseActive = isMouseActive;
}

void HealingTouchToolState::draw(sf::RenderWindow *window, bool active) {
  if (!active) return;
  if (starLineObject) {
    starLineObject->draw(window);
  }
}

void HealingTouchToolState::deselect() {
  if (starLineObject) {
    delete starLineObject;
    starLineObject = NULL;
  }
  hasBaseVector = false;
  lastMouseActive = false;
}

HealingTouchToolState::~HealingTouchToolState() {
  deselect();
}
