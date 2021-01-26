#include "scalpeltool.h"

void ScalpelToolState::initScalpel() {
  rawLineObject = new FreeFormLineObject(global, sf::Color(255, 0, 0, 64));
  rawLineObject->addPoint();
}

void ScalpelToolState::destroyScalpel() {
  delete rawLineObject;
  rawLineObject = NULL;
}

void ScalpelToolState::processScalpel() {
  rawLineObject->addPoint();
}

void ScalpelToolState::update(const sf::Time &t, bool active) {
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  if (lastMouseActive && isMouseActive) {
    // mouse is still active
    processScalpel();
  } else if (lastMouseActive) {
    // mouse is no longer active
    destroyScalpel();
  } else if (isMouseActive) {
    // mouse is now active
    initScalpel();
  }
  lastMouseActive = isMouseActive;
}

void ScalpelToolState::draw(sf::RenderWindow *window, bool active) {
  if (!active) return;
  if (rawLineObject) {
    rawLineObject->draw(window);
  }
}

void ScalpelToolState::deselect() {
  if (rawLineObject) {
    delete rawLineObject;
    rawLineObject = NULL;
  }
  lastMouseActive = false;
}

ScalpelToolState::~ScalpelToolState() {
  deselect();
}
