#ifndef STATE_SYRINGETOOL_H
#define STATE_SYRINGETOOL_H

#include <SFML/Graphics.hpp>

#include "commontool.h"

class SyringeToolState: public CommonToolState {
  private:
    static const sf::Vector2i vialPosition;
    static constexpr unsigned int vialRadius = 20;
    static constexpr unsigned int tubeAngle = 30;
    static constexpr int width = 16;
    static constexpr int height = 70;
    static constexpr double timeToFill = 0.8;
    static constexpr double timeToEmpty = 0.6;
    static constexpr unsigned int fullHeal = 12;

    sf::Vector2i lockedPosition;
    bool lastMouseActive = false;
    bool drawTube = false;
    bool filling = false;
    double filled = 0;

    void initSyringe();
    void stopSyringe();
    void processSyringe(const sf::Time &time);
    void drawTubePositions(sf::VertexArray &tube);

  public:
    SyringeToolState(GlobalValues *g, CommonPatientState *p) : CommonToolState(g, p) {}
    ~SyringeToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
