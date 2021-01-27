#include "operation.h"

const sf::Vector2i OperationState::timerPosition = sf::Vector2i(1250, 50);
const sf::Vector2i OperationState::timerHeaderOffset = sf::Vector2i(0, -20);

void OperationState::drawTime(sf::RenderWindow *window) {
  std::string timerStr = "";
  timerStr += padIntToString((timer/60), 2, '0');
  timerStr += ":" + padIntToString((int)timer%60, 2, '0');
  double remainder = timer - (int)timer;
  timerStr += "." + padIntToString(remainder*1000, 3, '0');
  timerText->setContent(timerStr);
  timerText->draw(window);
  timerHeaderText->draw(window);
}

void OperationState::update(const sf::Time &time) {
  double elapsed = time.asMicroseconds() / 1000000.0;
  timer += elapsed;
  toolSelect->update(time);
  vitals->update(time);
  score->update(time);
}

void OperationState::draw(sf::RenderWindow *window) {
  toolSelect->draw(window);
  vitals->draw(window);
  score->draw(window);
  drawTime(window);
}

OperationState::OperationState(GlobalValues *global) : CommonState(global) {
  score = new ScoreState(global);
  vitals = new VitalsState(global, 70, 99, 400);
  toolSelect = new ToolSelectState(global, vitals);
  timerText = new TextObject(global, timerPosition, sf::Color::White, 16);
  sf::Vector2i headerPosition = timerPosition + timerHeaderOffset;
  timerHeaderText = new TextObject(global, headerPosition, sf::Color::White, 16);
  timerHeaderText->setContent("Operation Time");
}

OperationState::~OperationState() {
  if (toolSelect) {
    delete toolSelect;
    toolSelect = NULL;
  }
  if (score) {
    delete score;
    score = NULL;
  }
  if (vitals) {
    delete vitals;
    vitals = NULL;
  }
  if (timerText) {
    delete timerText;
    timerText = NULL;
  }
  if (timerHeaderText) {
    delete timerHeaderText;
    timerHeaderText = NULL;
  }
}
