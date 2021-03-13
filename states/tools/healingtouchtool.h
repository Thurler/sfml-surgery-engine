#ifndef STATE_HEALINGTOUCHTOOL_H
#define STATE_HEALINGTOUCHTOOL_H

#include <SFML/Graphics.hpp>
#include "math.h"

#include "../../objects/freeformline.h"
#include "commontool.h"

class HealingTouchToolState: public CommonToolState {
  private:
    static constexpr int basePivotDistance = 30;
    static constexpr int iterPivotDistance = 7;
    static constexpr double iterAngleTolerance = M_PI / 6;

    FreeFormLineObject *starLineObject = NULL;
    sf::Vector2i basePivot;
    sf::Vector2i iterPivot;
    sf::Vector2i iterVector;
    bool hasBaseVector = false;
    bool lastMouseActive = false;

    void initStar();
    void destroyStar();
    void processStar();

  public:
    HealingTouchToolState(GlobalValues *g, CommonPatientState *p) : CommonToolState(g, p) {}
    ~HealingTouchToolState();

    void deselect();
    void update(const sf::Time &t, bool active);
    void draw(sf::RenderWindow *w, bool active);
};

#endif
