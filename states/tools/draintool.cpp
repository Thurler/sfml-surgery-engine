#include "draintool.h"

void DrainToolState::processDrain() {
}

void DrainToolState::update(const sf::Time &time, bool active) {
  processDrain();
}

void DrainToolState::draw(sf::RenderWindow *window, bool active) {
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  if (isMouseActive) {
    sf::Vector2i cursor = global->getMousePos();
    sf::VertexArray tube(sf::LineStrip, 4);
    tube[0].position = sf::Vector2f(cursor.x - width/2, 0);
    tube[1].position = sf::Vector2f(cursor.x - width/2, cursor.y);
    tube[2].position = sf::Vector2f(cursor.x + width/2, cursor.y);
    tube[3].position = sf::Vector2f(cursor.x + width/2, 0);
    for (int i = 0; i < 4; i++) {
      tube[i].color = sf::Color::White;
    }
    window->draw(tube);
  }
}

void DrainToolState::deselect() {
}

DrainToolState::~DrainToolState() {
  deselect();
}
