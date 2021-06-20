#pragma once
#include "CollidableObstacle.h"

#define BRICK_STATE_ACTIVE 10
#define BRICK_STATE_BROKEN 66

#define BRICK_ANI_ACTIVE 0

class BreakableBrick :
    public CollidableObstacle
{
public:

    BreakableBrick() { this->State = BRICK_STATE_ACTIVE; }
    void Render();
    void setState(int State);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

