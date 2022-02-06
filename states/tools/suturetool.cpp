#include "suturetool.h"

void SutureToolState::initSuture() {
  rawLineObject = new FreeFormLineObject(global, sf::Color(255, 255, 255, 32));
  rawLineObject->addPoint();
  sutureLineObject = new FreeFormLineObject(global, sf::Color::White);
  sutureLineObject->addPoint();
  basePivot = global->getMousePos();
}

void SutureToolState::destroySuture() {
  hasBaseVector = false;
  delete rawLineObject;
  rawLineObject = NULL;
  delete sutureLineObject;
  sutureLineObject = NULL;
}

void SutureToolState::processSuture() {
  rawLineObject->addPoint();
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
        sutureLineObject->addPoint();
        hasBaseVector = false;
      } else {
        // iterate pivot to where we are now
        iterPivot = currentPos;
        iterVector = curIterVector;
      }
    }
  }
}

void SutureToolState::update(bool active) {
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  if (lastMouseActive && isMouseActive) {
    // mouse is still active
    processSuture();
  } else if (lastMouseActive) {
    // mouse is no longer active
    destroySuture();
  } else if (isMouseActive) {
    // mouse is now active
    initSuture();
  }
  lastMouseActive = isMouseActive;
}

void SutureToolState::draw(sf::RenderWindow *window, bool active) {
  if (!active) return;
  if (rawLineObject) {
    rawLineObject->draw(window);
  }
  if (sutureLineObject) {
    sutureLineObject->draw(window);
  }
}

void SutureToolState::deselect() {
  if (rawLineObject) {
    delete rawLineObject;
    rawLineObject = NULL;
  }
  if (sutureLineObject) {
    delete sutureLineObject;
    sutureLineObject = NULL;
  }
  hasBaseVector = false;
  lastMouseActive = false;
}

SutureToolState::~SutureToolState() {
  deselect();
}
