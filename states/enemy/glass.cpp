#include "glass.h"

bool GlassShardState::checkAndResetDropped() {
  if (!dropped) return false;
  dropped = false;
  // drop max score the more it has been dropped
  dropCount = std::min(dropCount+1, (unsigned int)2);
  if (dropCount > 1) {
    grade = ScoreGrade::Bad;
  } else if (dropCount > 0) {
    grade = ScoreGrade::Good;
  }
  return true;
}

bool GlassShardState::grabForceps(const sf::Vector2i &position) {
  bool collided = shard->checkCollision(position);
  if (collided) {
    offset = position - sf::Vector2i(shard->getBasePosition());
  }
  return collided;
}

bool GlassShardState::updateForceps(const sf::Vector2i &position) {
  shard->setPosition(position - offset);
  if (shard->checkMistake()) return false;
  if (!removed && shard->checkRemoved()) {
    shard->setRemoved(true);
    double angleFactor = shard->getExitAngleFactor();
    if (angleFactor > 0.9 && grade > ScoreGrade::Bad) {
      grade = ScoreGrade::Bad;
    } else if (angleFactor > 0.75 && grade > ScoreGrade::Good) {
      grade = ScoreGrade::Good;
    }
    removed = true;
  }
  return true;
}

void GlassShardState::releaseForceps(bool tray) {
  if (tray) {
    disposed = true;
    return;
  }
  shard->resetPosition();
  shard->setRemoved(false);
  dropped = true;
  removed = false;
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
