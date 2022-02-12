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

bool GlassShard::checkMistake() {
  if (removed) return false;
  float effectiveHeight = getEffectiveHeight();
  if (effectiveHeight < (height / 6)) return true;

  sf::Vector2f p = position + ((-unit) * effectiveHeight);
  sf::Vector2f pivot = sf::Vector2f(p.x - positionA.x, p.y - positionA.y);
  double angle = getAngle(unitCut, pivot);
  if (angle > M_PI / 2) return true;

  p += (unitCut * width);
  pivot = sf::Vector2f(positionB.x - p.x, positionB.y - p.y);
  angle = getAngle(unitCut, pivot);
  if (angle > M_PI / 2) return true;

  return false;
}

bool GlassShard::checkRemoved() {
  if (removed) return true;
  float effectiveHeight = getEffectiveHeight();
  return effectiveHeight >= height;
}

double GlassShard::getExitAngleFactor() {
  // Compute pivot points
  sf::Vector2f perfectPoint = basePosition + (unit * height / 3.0f);
  sf::Vector2f maxLateralPoint = basePosition + (unitCut * offset);

  // Compute perfect and worst vectors - max angle
  sf::Vector2f perfect = perfectPoint - basePosition;
  sf::Vector2f worst = perfectPoint - maxLateralPoint;
  double maxAngle = getAngle(perfect, worst);

  // Compute current vector - current angle
  sf::Vector2f current = position - basePosition;
  double currentAngle = getAngle(perfect, current);

  return currentAngle/maxAngle;
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
  offset = (SmallCut::length - width) / 2.0f;
  position = positionA + (unitCut * offset);
  position += (unit * height / 1.5f);
  basePosition = position;
}
