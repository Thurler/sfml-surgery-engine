#include "glass.h"
#include "smallcut.h"
#include "math.h"

float GlassShard::getEffectiveHeight() {
  if (removed) return height;
  float dist = getDistance(position, positionA);
  sf::Vector2f distV(positionA.x - position.x, positionA.y - position.y);
  float angle = getAngle(distV, unitCut);
  return std::min(dist * sin(angle) - 2, height);
}

bool GlassShard::checkCollision(const sf::Vector2i &target) {
  // check if point inside rectangle - project it on both axis
  sf::Vector2f posH = position + (unitCut * width);
  float effectiveHeight = getEffectiveHeight();
  sf::Vector2f posV = position + ((-unit) * effectiveHeight);
  sf::Vector2f horizontal = sf::Vector2f(posH.x - position.x, posH.y - position.y);
  sf::Vector2f vertical = sf::Vector2f(posV.x - position.x, posV.y - position.y);
  sf::Vector2f targetVector = sf::Vector2f(target.x - position.x, target.y - position.y);
  double scalarH = scalarProjection(targetVector, horizontal);
  double scalarV = scalarProjection(targetVector, vertical);
  return (scalarH >= 0 && scalarH <= width && scalarV >= 0 && scalarV <= effectiveHeight);
}

void GlassShard::draw(sf::RenderWindow *window) {
  sf::ConvexShape shard;
  shard.setPointCount(4);
  shard.setFillColor(sf::Color(255, 255, 255, 128));
  shard.setOutlineColor(sf::Color(255, 255, 255, 128));
  shard.setOutlineThickness(2);
  float effectiveHeight = getEffectiveHeight();
  sf::Vector2f p = position;
  shard.setPoint(0, p);
  p += (unitCut * width);
  shard.setPoint(1, p);
  p += ((-unit) * effectiveHeight);
  shard.setPoint(2, p);
  p += ((-unitCut) * width);
  shard.setPoint(3, p);
  window->draw(shard);
}

GlassShard::GlassShard(
  GlobalValues *global, const sf::Vector2i &pos, double angle
) : CommonObject(global) {
  unitCut = unitAtAngle(angle);
  unit = unitAtAngle(angle - (M_PI / 2));
  positionA = sf::Vector2f(pos.x, pos.y);
  positionB = positionA + (unitCut * SmallCut::length);
  float offset = (SmallCut::length - width) / 2.0f;
  position = positionA + (unitCut * offset);
  position += (unit * height / 2.0f);
  basePosition = position;
}
