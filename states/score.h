#ifndef STATE_SCORE_H
#define STATE_SCORE_H

#include <SFML/Graphics.hpp>

#include "common.h"
#include "../objects/text.h"

class ScoreState: public CommonState {
  private:
    static const sf::Vector2i scorePosition;
    static const sf::Vector2i scoreHeaderOffset;
    static constexpr unsigned int maxChange = 9;

    unsigned long score = 0;
    unsigned long pendingScore = 0;
    TextObject *scoreText = NULL;
    TextObject *scoreHeaderText = NULL;

  public:
    ScoreState(GlobalValues *g);
    ~ScoreState();

    void update();
    void draw(sf::RenderWindow *w);
    void receiveScore(unsigned long s) { pendingScore += s; }
};

#endif
