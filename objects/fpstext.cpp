#include <string>
#include "math.h"

#include "fpstext.h"

void FPSTextObject::update(const sf::Time &time) {
  unsigned int fps = round(1000000.0f / time.asMicroseconds());
  lastValues[index++] = fps;
  if (index >= limit) index = 0;
  unsigned int sum = 0;
  unsigned int count = 0;
  for (unsigned int i = 0; i < limit; i++) {
    if (lastValues[i] != 0) {
      sum += lastValues[i];
      count++;
    }
  }
  fps = round(1.0 * sum / count);
  setContent(std::to_string(fps) + " fps");
}
