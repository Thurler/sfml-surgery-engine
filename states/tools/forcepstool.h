#ifndef STATE_FORCEPSTOOL_H
#define STATE_FORCEPSTOOL_H

#include <SFML/Graphics.hpp>

#include "../enemy/common.h"
#include "commontool.h"

#include "math.h"

class ForcepsToolState: public CommonToolState {
  private:
    static const sf::Vector2i trayPosition;
    static constexpr unsigned int trayRadius = 80;
    static constexpr double trayEllipseScale = 3;

    bool lastMouseActive = false;
    CommonEnemyState *heldItem = NULL;

    bool insideTray(const sf::Vector2i &position);

  public:
    ForcepsToolState(GlobalValues *g, CommonPatientState *p) : CommonToolState(g, p) {}
    ~ForcepsToolState();

    void deselect();
    void update(bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
