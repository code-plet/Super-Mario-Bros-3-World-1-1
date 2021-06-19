#pragma once
#include "CGameObject.h"

#define OBSTACLE_ANI 0

class CollidableObstacle :
    public CGameObject
{
protected:
    bool TopOnly;
public:

    CollidableObstacle() {}
    CollidableObstacle(bool top_only) { this->TopOnly = top_only; }

    bool GetTopOnly() { return TopOnly; }

    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

