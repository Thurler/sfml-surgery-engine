#ifndef STATE_OPERATION_H
#define STATE_OPERATION_H

#include <SFML/Graphics.hpp>

#include "common.h"
#include "vitals.h"
#include "tools/toolselect.h"

class OperationState: public CommonState {
  private:
    VitalsState *vitals;
    ToolSelectState *toolSelect;

  public:
    OperationState(GlobalValues *g);
    ~OperationState();

    void update(const sf::Time &t);
    void draw(sf::RenderWindow *w);
};

#endif
