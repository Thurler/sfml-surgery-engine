#include "geltool.h"

void GelToolState::initRipple(bool small) {
  sf::Vector2i center = global->getMousePos();
  Ripple *ripple;
  GelProperties *properties = new GelProperties(small);
  if (small) {
    ripple = new Ripple(
      center, sf::Color(0, 255, 0, 64), duration, 0.5, radius - 10, radius, properties
    );
  } else {
    ripple = new Ripple(
      center, sf::Color(0, 255, 0, 64), duration, 0.5, radius, radius + 10, properties
    );
    timer = cooldown;
  }
  ripples.push_back(ripple);
  lastCenter = center;
}

void GelToolState::updateRipples(const sf::Time &time) {
  // update ongoing ripples, check for expired
  std::vector<unsigned long> expired;
  double elapsed = global->getElapsedTime();
  double healed = (elapsed/duration)*fullHeal;
  for (unsigned long i = 0; i < ripples.size(); i++) {
    if (ripples[i]->hasExpired()) {
      expired.push_back(i);
    } else {
      ripples[i]->update(time);
    }
  }
  // removed expired ripples, if any
  for (unsigned long i = expired.size(); i > 0; i--) {
    unsigned long index = expired[i-1];
    delete ripples[index];
    ripples.erase(ripples.begin() + index);
  }
  patient->interactGel(ripples, healed);
}

void GelToolState::update(const sf::Time &time, bool active) {
  updateRipples(time);
  // decrement cooldown timer if above 0
  if (timer > 0) {
    timer -= time.asMicroseconds() / 1000000.0f;
    if (timer < 0) {
      timer = 0;
    }
  }
  // check input for a new ripple, but only if active
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  if (isMouseActive) {
    // check cooldown to spawn new big ripple
    if (timer <= 0) {
      initRipple(false);
    } else if (getDistance(global->getMousePos(), lastCenter) >= radius) {
      // otherwise, check distance to spawn new small ripple
      initRipple(true);
    }
  }
}

void GelToolState::draw(sf::RenderWindow *window, bool active) {
  // draw ongoing ripples
  for (unsigned long i = 0; i < ripples.size(); i++) {
    ripples[i]->draw(window);
  }
}

void GelToolState::deselect() {
}

GelToolState::~GelToolState() {
  deselect();
  for (unsigned long i = 0; i < ripples.size(); i++) {
    delete ripples[i];
  }
}
