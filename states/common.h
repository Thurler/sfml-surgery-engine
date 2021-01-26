#ifndef STATE_COMMON_H
#define STATE_COMMON_H

#include "../objects/common.h"
#include "../global.h"

class CommonState: public CommonObject {
  protected:
    CommonState(GlobalValues *g) : CommonObject(g) {}
  public:
    virtual ~CommonState() {}
};

#endif
