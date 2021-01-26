#include "math.h"

#include "toolselect.h"

#include "geltool.h"
#include "draintool.h"
#include "lasertool.h"
#include "suturetool.h"
#include "forcepstool.h"
#include "scalpeltool.h"
#include "syringetool.h"
#include "ultrasoundtool.h"
#include "healingtouchtool.h"

const sf::Vector2i ToolSelectState::toolPosition = sf::Vector2i(70, 630);

void ToolSelectState::update(const sf::Time &time) {
  // handle tool wheel input
  bool isKeyUp = global->getKeyUp();
  bool isKeyDown = global->getKeyDown();
  bool isKeyLeft = global->getKeyLeft();
  bool isKeyRight = global->getKeyRight();
  bool isKeySpecial = global->getKeySpecial();

  CommonToolState *newTool = NULL;
  if (!lastKeySpecial && isKeySpecial) {
    // pushed special key - select healing touch
    newTool = tools[Tool::HealingTouch];
  } else if ((!lastKeyUp || !lastKeyLeft) && isKeyLeft && isKeyUp) {
    // pushed up left key - select forceps
    newTool = tools[Tool::Forceps];
  } else if ((!lastKeyUp || !lastKeyRight) && isKeyRight && isKeyUp) {
    // pushed up right key - select syringe
    newTool = tools[Tool::Syringe];
  } else if ((!lastKeyDown || !lastKeyLeft) && isKeyLeft && isKeyDown) {
    // pushed down left key - select ultrasound
    newTool = tools[Tool::Ultrasound];
  } else if ((!lastKeyDown || !lastKeyRight) && isKeyRight && isKeyDown) {
    // pushed down right key - select drain
    newTool = tools[Tool::Drain];
  } else if (!lastKeyUp && isKeyUp) {
    // pushed up key - select gel
    newTool = tools[Tool::Gel];
  } else if (!lastKeyLeft && isKeyLeft) {
    // pushed left key - select scalpel
    newTool = tools[Tool::Scalpel];
  } else if (!lastKeyDown && isKeyDown) {
    // pushed down key - select laser
    newTool = tools[Tool::Laser];
  } else if (!lastKeyRight && isKeyRight) {
    // pushed right key - select suture
    newTool = tools[Tool::Suture];
  }
  if (newTool) {
    if (currentTool) currentTool->deselect();
    currentTool = newTool;
  }

  lastKeyUp = isKeyUp;
  lastKeyDown = isKeyDown;
  lastKeyLeft = isKeyLeft;
  lastKeyRight = isKeyRight;
  lastKeySpecial = isKeySpecial;

  // handle specific tool updates
  for (unsigned int i = 0; i < toolCount; i++) {
    bool isCurrent = (tools[i] == currentTool);
    tools[i]->update(time, isCurrent);
  }

}

void ToolSelectState::draw(sf::RenderWindow *window) {
  // draw tools
  for (unsigned int i = 0; i < toolCount; i++) {
    bool isCurrent = (tools[i] == currentTool);
    tools[i]->draw(window, isCurrent);
  }
  // draw tool select
  for (unsigned int i = 0; i < 8; i++) {
    sf::CircleShape tool(toolRadius);
    if (currentTool && currentTool == tools[i]) {
      tool.setFillColor(sf::Color::Red);
    } else {
      tool.setFillColor(sf::Color::White);
    }
    int offsetX = cos(i*M_PI/4) * wheelRadius;
    int offsetY = sin(i*M_PI/4) * wheelRadius;
    sf::Vector2i position = toolPosition + sf::Vector2i(offsetX, offsetY);
    tool.setPosition(position.x, position.y);
    window->draw(tool);
  }
}

ToolSelectState::ToolSelectState(GlobalValues *global, VitalsState *v) :
vitals(v), CommonState(global) {
  tools[Tool::Suture] = new SutureToolState(global, v);
  tools[Tool::Syringe] = new SyringeToolState(global, v);
  tools[Tool::Gel] = new GelToolState(global, v);
  tools[Tool::Forceps] = new ForcepsToolState(global, v);
  tools[Tool::Scalpel] = new ScalpelToolState(global, v);
  tools[Tool::Ultrasound] = new UltrasoundToolState(global, v);
  tools[Tool::Laser] = new LaserToolState(global, v);
  tools[Tool::Drain] = new DrainToolState(global, v);
  tools[Tool::HealingTouch] = new HealingTouchToolState(global, v);
}

ToolSelectState::~ToolSelectState() {
  for (unsigned int i = 0; i < toolCount; i++) {
    if (tools[i]) {
      delete tools[i];
    }
  }
}
