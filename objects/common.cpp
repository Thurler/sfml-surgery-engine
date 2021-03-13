#include "common.h"
#include "math.h"

sf::Vector2f CommonObject::unitAtAngle(double angle) {
  return sf::Vector2f(cos(angle), sin(angle));
}

double CommonObject::getDistance(sf::Vector2i a, sf::Vector2i b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double CommonObject::getDistance(sf::Vector2f a, sf::Vector2i b) {
  return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double CommonObject::getAngle(sf::Vector2i a, sf::Vector2i b) {
  double dot = (a.x * b.x) + (a.y * b.y);
  double prod = sqrt(pow(a.x, 2) + pow(a.y, 2)) * sqrt(pow(b.x, 2) + pow(b.y, 2));
  return acos(dot/prod);
}

std::string CommonObject::padIntToString(long value, unsigned int size, char padding) {
  std::string str = std::to_string(value);
  unsigned int current = str.size();
  if (size > current) {
    str.insert(0, size-current, padding);
  }
  return str;
}
