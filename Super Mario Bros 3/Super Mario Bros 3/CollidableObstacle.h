#pragma once
#include "CGameObject.h"

#define OBSTACLE_ANI 0

class CollidableObstacle :
    public CGameObject
{
protected:

public:

    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

