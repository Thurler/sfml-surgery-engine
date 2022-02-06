#include "ultrasoundtool.h"

void UltrasoundToolState::initRipple() {
  sf::Vector2i center = global->getMousePos();
  Ripple *ripple = new Ripple(
    global, center, sf::Color(255, 255, 255, 64), 0.7, 0.25, 50, 70, NULL
  );
  ripples.push_back(ripple);
  timer = cooldown;
}

void UltrasoundToolState::updateRipples() {
  // update ongoing ripples, check for expired
  std::vector<unsigned long> expired;
  for (unsigned long i = 0; i < ripples.size(); i++) {
    if (ripples[i]->hasExpired()) {
      expired.push_back(i);
    } else {
      ripples[i]->update();
    }
  }
  // removed expired ripples, if any
  for (unsigned long i = expired.size(); i > 0; i--) {
    unsigned long index = expired[i-1];
    delete ripples[index];
    ripples.erase(ripples.begin() + index);
  }
}

void UltrasoundToolState::update(bool active) {
  updateRipples();
  // decrement cooldown timer if above 0
  if (timer > 0) {
    timer -= global->getElapsedTime();
    if (timer < 0) {
      timer = 0;
    }
  }
  // check input for a new ripple, but only if active and not in cooldown
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  if (!lastMouseActive && isMouseActive) {
    // mouse is now active, check cooldown to spawn new ripple
    if (timer <= 0) {
      initRipple();
    }
  }
  lastMouseActive = isMouseActive;
}

void UltrasoundToolState::draw(sf::RenderWindow *window, bool active) {
  // draw ongoing ripples
  for (unsigned long i = 0; i < ripples.size(); i++) {
    ripples[i]->draw(window);
  }
}

void UltrasoundToolState::deselect() {
  lastMouseActive = false;
}

UltrasoundToolState::~UltrasoundToolState() {
  deselect();
  for (unsigned long i = 0; i < ripples.size(); i++) {
    delete ripples[i];
  }
}
