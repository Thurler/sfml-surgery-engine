#include "glass.h"

bool GlassShardState::isDisposed() {
  return false;
}

bool GlassShardState::grabForceps(const sf::Vector2i &position) {
  bool collided = shard->checkCollision(position);
  if (collided) {
    offset = position - sf::Vector2i(shard->getBasePosition());
  }
  return collided;
}

void GlassShardState::updateForceps(const sf::Vector2i &position) {
  shard->setPosition(position - offset);
}

void GlassShardState::releaseForceps() {
  shard->resetPosition();
  shard->setRemoved(false);
}

void GlassShardState::draw(sf::RenderWindow *window) {
  shard->draw(window);
}

GlassShardState::GlassShardState(
  GlobalValues *global, const sf::Vector2i &position, double angle
) : CommonEnemyState(global) {
  shard = new GlassShard(global, position, angle);
}

GlassShardState::~GlassShardState() {
  if (shard != NULL) {
    delete shard;
  }
}
