#include "lasertool.h"

void LaserToolState::processLaser() {
}

void LaserToolState::update(const sf::Time &t, bool active) {
  processLaser();
}

void LaserToolState::draw(sf::RenderWindow *window, bool active) {
  if (!active) return;
  bool isMouseActive = global->getMouseActive();
  if (isMouseActive) {
    sf::Vector2i cursor = global->getMousePos();
    int offsetX = cursor.y/tan(slope);
    sf::VertexArray beam(sf::LineStrip, 4);
    beam[0].position = sf::Vector2f(cursor.x - width/2 + offsetX, 0);
    beam[1].position = sf::Vector2f(cursor.x - width/2, cursor.y);
    beam[2].position = sf::Vector2f(cursor.x + width/2, cursor.y);
    beam[3].position = sf::Vector2f(cursor.x + offsetX + width/2, 0);
    for (int i = 0; i < 4; i++) {
      beam[i].color = sf::Color::Cyan;
    }
    window->draw(beam);
  }
}

void LaserToolState::deselect() {
}

LaserToolState::~LaserToolState() {
  deselect();
}
