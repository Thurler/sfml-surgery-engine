#include "ultrasoundtool.h"

void UltrasoundToolState::initRipple() {
  sf::Vector2i center = global->getMousePos();
  Ripple *ripple = new Ripple(
    center, sf::Color(255, 255, 255, 64), 0.7, 0.25, 50, 70, NULL
  );
  ripples.push_back(ripple);
  timer = cooldown;
}

void UltrasoundToolState::updateRipples(const sf::Time &time) {
  // update ongoing ripples, check for expired
  std::vector<unsigned int> expired;
  for (unsigned int i = 0; i < ripples.size(); i++) {
    if (ripples[i]->hasExpired()) {
      expired.push_back(i);
    } else {
      ripples[i]->update(time);
    }
  }
  // removed expired ripples, if any
  for (unsigned int i = expired.size(); i > 0; i--) {
    unsigned int index = expired[i-1];
    delete ripples[index];
    ripples.erase(ripples.begin() + index);
  }
}

void UltrasoundToolState::update(const sf::Time &time, bool active) {
  updateRipples(time);
  // decrement cooldown timer if above 0
  if (timer > 0) {
    timer -= time.asMicroseconds() / 1000000.0f;
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
  for (unsigned int i = 0; i < ripples.size(); i++) {
    ripples[i]->draw(window);
  }
}

void UltrasoundToolState::deselect() {
  lastMouseActive = false;
}

UltrasoundToolState::~UltrasoundToolState() {
  deselect();
  for (unsigned int i = 0; i < ripples.size(); i++) {
    delete ripples[i];
  }
}
