#pragma once
#include "CGameObject.h"

#define GROUND_ANI 0

class Ground :
    public CGameObject
{
protected:

    float height, width;

public:

    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

