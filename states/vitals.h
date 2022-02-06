#ifndef STATE_VITALS_H
#define STATE_VITALS_H

#include <SFML/Graphics.hpp>

#include "common.h"
#include "../objects/text.h"

class VitalsState: public CommonState {
  private:
    static const sf::Vector2i vitalsPosition;
    static const sf::Vector2i fullVitalsOffset;
    static const sf::Vector2i vitalBarOffset;
    static const sf::Vector2i fullVitalBarOffset;
    static const sf::Color normalColor;
    static const sf::Color warningColor;
    static const sf::Color dangerColor;
    static constexpr unsigned int barWidth = 500;
    static constexpr unsigned int barHeight = 25;
    static constexpr unsigned int fullBarWidth = 110;
    static constexpr unsigned int fullBarHeight = 15;
    static constexpr unsigned int maxChangePerSecond = 30;

    double startingFull;
    double currentFull;
    double gaugeMax;
    double current;
    double accumulatedPermDamage = 0;
    double accumulatedDamage = 0;
    double accumulatedHeal = 0;
    TextObject *currentText = NULL;
    TextObject *currentFullText = NULL;

    void applyPermDamage(double amount);
    void applyDamage(double amount);
    void applyHeal(double amount);
    void drawCurrent(sf::RenderWindow *w);
    void drawCurrentFull(sf::RenderWindow *w);
    const sf::Color & getColorGrade(double value);

  public:
    VitalsState(GlobalValues *g, double c, double m, double f);
    ~VitalsState();

    void update(const sf::Time &t);
    void draw(sf::RenderWindow *w);
    void receiveDamage(double damage) { accumulatedDamage += damage; }
    void receivePermDamage(double damage) { accumulatedPermDamage += damage; }
    void receiveHeal(double heal) { accumulatedHeal += heal; }
};

#endif
