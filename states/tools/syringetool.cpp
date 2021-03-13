#include "math.h"
#include "syringetool.h"

const sf::Vector2i SyringeToolState::vialPosition = sf::Vector2i(1000, 530);

void SyringeToolState::initSyringe() {
  sf::Vector2i mousePos = global->getMousePos();
  // lock filling state for next frame
  filling = (getDistance(mousePos, vialPosition) <= vialRadius);
  // lock cursor in place
  if (filling) {
    lockedPosition = vialPosition;
  } else {
    lockedPosition = mousePos;
  }
  drawTube = true;
}

void SyringeToolState::stopSyringe() {
  drawTube = false;
}

void SyringeToolState::processSyringe(const sf::Time &time) {
  if (filling || filled > 0) {
    // keep cursor locked in place
    global->setMousePos(lockedPosition);
  }
  double elapsed = time.asMicroseconds() / 1000000.0f;
  if (filling) {
    filled += (elapsed/timeToFill);
    if (filled > 1) filled = 1;
  } else {
    double healed = (elapsed/timeToEmpty);
    filled -= healed;
    if (filled < 0) {
      healed += filled;
      filled = 0;
    }
    healed *= fullHeal;
    // vitals->receiveHeal(healed);
  }
}

void SyringeToolState::update(const sf::Time &time, bool active) {
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  if (lastMouseActive && isMouseActive) {
    // mouse is still active
    processSyringe(time);
  } else if (lastMouseActive) {
    // mouse is no longer active
    stopSyringe();
  } else if (isMouseActive) {
    // mouse is now active
    initSyringe();
  }
  lastMouseActive = isMouseActive;
}

void SyringeToolState::drawTubePositions(sf::VertexArray &tube) {
  tube[0].position = sf::Vector2f(lockedPosition.x - width/2, lockedPosition.y - height);
  tube[1].position = sf::Vector2f(lockedPosition.x - width/2, lockedPosition.y);
  tube[2].position = sf::Vector2f(lockedPosition.x + width/2, lockedPosition.y);
  tube[3].position = sf::Vector2f(lockedPosition.x + width/2, lockedPosition.y - height);
  tube[4].position = sf::Vector2f(lockedPosition.x + width/2, lockedPosition.y - height*filled);
  tube[5].position = sf::Vector2f(lockedPosition.x - width/2, lockedPosition.y - height*filled);
}

void SyringeToolState::draw(sf::RenderWindow *window, bool active) {
  if (!active) return;
  // draw stabilizer vial
  sf::CircleShape vial(vialRadius);
  vial.setFillColor(sf::Color(0, 255, 0, 128));
  vial.setPosition(vialPosition.x - vialRadius, vialPosition.y - vialRadius);
  window->draw(vial);
  // draw tube if it is active
  if (drawTube && (filling || filled > 0)) {
    sf::RectangleShape fill(sf::Vector2f(width, -height*filled));
    fill.setOrigin(width/2, 0);
    fill.setPosition(sf::Vector2f(lockedPosition.x, lockedPosition.y));
    fill.setFillColor(sf::Color(0, 255, 0, 128));
    sf::VertexArray tube(sf::LineStrip, 6);
    drawTubePositions(tube);
    for (int i = 0; i < 6; i++) {
      tube[i].color = sf::Color::White;
    }
    sf::Transform transform;
    if (!filling){
      transform.rotate(tubeAngle, lockedPosition.x, lockedPosition.y);
      fill.rotate(tubeAngle);
    }
    window->draw(fill);
    window->draw(tube, transform);
  }
}

void SyringeToolState::deselect() {
  lastMouseActive = false;
  filling = false;
  drawTube = false;
}

SyringeToolState::~SyringeToolState() {
  deselect();
}
