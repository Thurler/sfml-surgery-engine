#ifndef STATE_GLASSENEMY_H
#define STATE_GLASSENEMY_H

#include "../../objects/glass.h"
#include "common.h"

class GlassShardState: public CommonEnemyState {
  private:
    ScoreGrade grade = ScoreGrade::Bad;
    unsigned int scores[3] = {30, 70, 110};
    unsigned int scoreValue() { return scores[grade]; }

    GlassShard *shard;
    sf::Vector2i offset;

  public:
    GlassShardState(GlobalValues *g, const sf::Vector2i &p, double a);
    ~GlassShardState();

    bool isDisposed();
    bool grabForceps(const sf::Vector2i &p);
    void updateForceps(const sf::Vector2i &p);
    void releaseForceps();

    void update() {}
    void draw(sf::RenderWindow *w);
};

#endif
