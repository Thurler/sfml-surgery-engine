#ifndef STATE_OPERATION_H
#define STATE_OPERATION_H

#include <SFML/Graphics.hpp>

#include "common.h"
#include "score.h"
#include "vitals.h"
#include "patient/common.h"
#include "tools/toolselect.h"
#include "../objects/text.h"

class OperationState: public CommonState {
  private:
    static const sf::Vector2i timerPosition;
    static const sf::Vector2i timerHeaderOffset;

    double timer = 0;
    ScoreState *score = NULL;
    VitalsState *vitals = NULL;
    CommonPatientState *patient = NULL;
    ToolSelectState *toolSelect = NULL;
    TextObject *timerText = NULL;
    TextObject *timerHeaderText = NULL;

    void drawTime(sf::RenderWindow *w);

  public:
    OperationState(GlobalValues *g);
    ~OperationState();

    void update(const sf::Time &t);
    void draw(sf::RenderWindow *w);
};

#endif
