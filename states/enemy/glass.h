#ifndef STATE_GLASSENEMY_H
#define STATE_GLASSENEMY_H

#include "../../objects/glass.h"
#include "common.h"

class GlassShardState: public CommonEnemyState {
  private:
    double flatDamage() { return 5; }
    double flatPermDamage() { return 1; }
    unsigned int scoreValue() { return scores[grade]; }

    bool dropped = false;
    bool removed = false;
    bool disposed = false;
    unsigned int dropCount = 0;
    GlassShard *shard;
    sf::Vector2i offset;
    ScoreGrade grade = ScoreGrade::Cool;
    unsigned int scores[3] = {30, 70, 110};

  public:
    GlassShardState(GlobalValues *g, const sf::Vector2i &p, double a);
    ~GlassShardState();

    bool checkAndResetDropped();
    bool isDisposed() { return disposed; }
    bool grabForceps(const sf::Vector2i &p);
    bool updateForceps(const sf::Vector2i &p);
    void releaseForceps(bool tray);

    void update() {}
    void draw(sf::RenderWindow *w);
};

#endif
