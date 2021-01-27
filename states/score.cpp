#include "score.h"

const sf::Vector2i ScoreState::scorePosition = sf::Vector2i(1250, 100);
const sf::Vector2i ScoreState::scoreHeaderOffset = sf::Vector2i(0, -20);

void ScoreState::update(const sf::Time &time) {
  if (pendingScore > 0) {
    if (pendingScore > maxChange) {
      score += maxChange;
      pendingScore -= maxChange;
    } else {
      score += pendingScore;
      pendingScore = 0;
    }
  }
}

void ScoreState::draw(sf::RenderWindow *window) {
  scoreText->setContent(std::to_string(score));
  scoreText->draw(window);
  scoreHeaderText->draw(window);
}

ScoreState::ScoreState(GlobalValues *global) : CommonState(global) {
  scoreText = new TextObject(global, scorePosition, sf::Color::White, 16);
  sf::Vector2i headerPosition = scorePosition + scoreHeaderOffset;
  scoreHeaderText = new TextObject(global, headerPosition, sf::Color::White, 16);
  scoreHeaderText->setContent("Operation Score");
}

ScoreState::~ScoreState() {
  if (scoreText) {
    delete scoreText;
    scoreText = NULL;
  }
  if (scoreHeaderText) {
    delete scoreHeaderText;
    scoreHeaderText = NULL;
  }
}
