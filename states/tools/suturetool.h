#ifndef STATE_SUTURETOOL_H
#define STATE_SUTURETOOL_H

#include <SFML/Graphics.hpp>
#include "math.h"

#include "../../objects/freeformline.h"
#include "commontool.h"

class SutureToolState: public CommonToolState {
  private:
    static constexpr int basePivotDistance = 30;
    static constexpr int iterPivotDistance = 7;
    static constexpr double iterAngleTolerance = M_PI / 6;

    FreeFormLineObject *rawLineObject = NULL;
    FreeFormLineObject *sutureLineObject = NULL;
    sf::Vector2i basePivot;
    sf::Vector2i iterPivot;
    sf::Vector2i iterVector;
    bool hasBaseVector = false;
    bool lastMouseActive = false;

    void initSuture();
    void destroySuture();
    void processSuture();

  public:
    SutureToolState(GlobalValues *g, VitalsState *v) : CommonToolState(g, v) {}
    ~SutureToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
