#ifndef STATE_COMMONENEMY_H
#define STATE_COMMONENEMY_H

#include "../common.h"

class CommonEnemyState: public CommonState {
  protected:
    CommonEnemyState(GlobalValues *g) : CommonState(g) {}
  public:
    virtual ~CommonEnemyState() {}
};

#endif
