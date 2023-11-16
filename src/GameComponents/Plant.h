#pragma once
#include "Entity.h"

class Plant :
    public Entity
{
public:
    inline void setLane(int l) { lane = l; }
    inline int getLane() { return lane; }

private:
    int lane = -1;
};

