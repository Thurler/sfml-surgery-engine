#ifndef STATE_SCALPELTOOL_H
#define STATE_SCALPELTOOL_H

#include <SFML/Graphics.hpp>

#include "../../objects/freeformline.h"
#include "commontool.h"

class ScalpelToolState: public CommonToolState {
  private:
    FreeFormLineObject *rawLineObject = NULL;
    bool lastMouseActive = false;

    void initScalpel();
    void destroyScalpel();
    void processScalpel();

  public:
    ScalpelToolState(GlobalValues *g, VitalsState *v) : CommonToolState(g, v) {}
    ~ScalpelToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
