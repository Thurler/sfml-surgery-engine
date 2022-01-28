#include "math.h"
#include "vitals.h"

const sf::Vector2i VitalsState::vitalsPosition = sf::Vector2i(60, 30);
const sf::Vector2i VitalsState::fullVitalsOffset = sf::Vector2i(30, 33);
const sf::Vector2i VitalsState::vitalBarOffset = sf::Vector2i(25, -16);
const sf::Vector2i VitalsState::fullVitalBarOffset = sf::Vector2i(45, 22);
const sf::Color VitalsState::normalColor = sf::Color(0, 200, 0, 255);
const sf::Color VitalsState::warningColor = sf::Color(200, 200, 0, 255);
const sf::Color VitalsState::dangerColor = sf::Color(200, 0, 0, 255);

void VitalsState::applyDamage(double damage) {
  currentFull -= damage;
  if (currentFull < 0) {
    currentFull = 0;
  }
  current -= damage;
  if (current < 0) {
    current = 0;
  }
  if (currentFull < gaugeMax) {
    gaugeMax = currentFull;
  }
  accumulatedDamage -= damage;
  if (accumulatedDamage < 0) {
    accumulatedDamage = 0;
  }
}

void VitalsState::applyHeal(double heal) {
  current += heal;
  if (current > gaugeMax) {
    current = gaugeMax;
  }
  accumulatedHeal -= heal;
  if (accumulatedHeal < 0) {
    accumulatedHeal = 0;
  }
}

void VitalsState::update(const sf::Time &time) {
  double elapsed = global->getElapsedTime();
  // For now, passively subtract 1 vital every 0.5 seconds
  double damage = elapsed*2;
  // receiveDamage(damage);
  // Check accumulated damage - apply damage/heal as necessary
  double limit = elapsed*maxChangePerSecond;
  if (accumulatedDamage > limit) {
    applyDamage(limit);
  } else if (accumulatedDamage > 0) {
    applyDamage(accumulatedDamage);
  }
  if (accumulatedHeal > limit) {
    applyHeal(limit);
  } else if (accumulatedHeal > 0) {
    applyHeal(accumulatedHeal);
  }
}

const sf::Color & VitalsState::getColorGrade(double value) {
  if (value >= 50) {
    return normalColor;
  } else if (value >= 25) {
    return warningColor;
  } else {
    return dangerColor;
  }
}

void VitalsState::drawCurrent(sf::RenderWindow *window) {
  sf::Color targetColor = getColorGrade(current);
  // update text content and color
  currentText->setContent(std::to_string((int)current));
  currentText->setColor(targetColor);
  // draw the vital bar outline
  sf::RectangleShape outline(sf::Vector2f(barWidth, barHeight));
  sf::Vector2i barPositionInt = vitalsPosition + vitalBarOffset;
  sf::Vector2f barPosition = sf::Vector2f(barPositionInt.x, barPositionInt.y);
  outline.setPosition(barPosition);
  outline.setFillColor(sf::Color(0, 0, 0, 0));
  outline.setOutlineColor(sf::Color::White);
  outline.setOutlineThickness(2);
  // draw the vital bar max background
  sf::RectangleShape maxBackground(sf::Vector2f(barWidth*(gaugeMax/99.0), barHeight));
  maxBackground.setPosition(barPosition);
  maxBackground.setFillColor(sf::Color(64, 64, 64, 255));
  // draw the vital bar current
  sf::RectangleShape currentVital(sf::Vector2f(barWidth*(current/99.0), barHeight));
  currentVital.setPosition(barPosition);
  currentVital.setFillColor(targetColor);
  // render things
  currentText->draw(window);
  window->draw(outline);
  window->draw(maxBackground);
  window->draw(currentVital);
}

void VitalsState::drawCurrentFull(sf::RenderWindow *window) {
  sf::Color targetColor = getColorGrade(currentFull);
  unsigned int targetBars = ceil(currentFull/100);
  // update text content and color
  currentFullText->setContent(std::to_string((int)currentFull));
  currentFullText->setColor(targetColor);
  // draw the vital bar outlines
  sf::RectangleShape outlines[4];
  sf::Vector2i barPositionInt = vitalsPosition + fullVitalBarOffset;
  sf::Vector2f barPosition = sf::Vector2f(barPositionInt.x, barPositionInt.y);
  for (unsigned int i = 0; i < targetBars; i++) {
    sf::RectangleShape outline(sf::Vector2f(fullBarWidth, fullBarHeight));
    outline.setPosition(barPosition + sf::Vector2f(fullBarWidth*i, 0));
    outline.setFillColor(sf::Color(0, 0, 0, 0));
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2);
    outlines[i] = outline;
  }
  // draw the vital bar current
  sf::RectangleShape currentFulls[4];
  for (unsigned int i = 0; i < targetBars; i++) {
    double currentBar = currentFull - 100*i;
    sf::Color targetColor = getColorGrade(currentBar);
    sf::RectangleShape currentFull(sf::Vector2f(fullBarWidth*(currentBar/100.0), fullBarHeight));
    currentFull.setPosition(barPosition + sf::Vector2f(fullBarWidth*i, 0));
    currentFull.setFillColor(targetColor);
    currentFulls[i] = currentFull;
  }
  // render things
  currentFullText->draw(window);
  for (unsigned int i = 0; i < targetBars; i++) {
    window->draw(outlines[i]);
    window->draw(currentFulls[i]);
  }
}

void VitalsState::draw(sf::RenderWindow *window) {
  drawCurrent(window);
  drawCurrentFull(window);
}

VitalsState::VitalsState(GlobalValues *g, double c, double m, double f) :
current(c), gaugeMax(m), currentFull(f), startingFull(f), CommonState(g) {
  currentText = new TextObject(g, vitalsPosition, sf::Color::White, 30);
  sf::Vector2i fullPosition = vitalsPosition + fullVitalsOffset;
  currentFullText = new TextObject(g, fullPosition, sf::Color::White, 15);
}

VitalsState::~VitalsState() {
  if (currentText) {
    delete currentText;
  }
  if (currentFullText) {
    delete currentFullText;
  }
}
