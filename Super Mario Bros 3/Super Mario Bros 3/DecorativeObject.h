#pragma once
#include "CGameObject.h"

#define DECORATIVEOBJECT_ANI 0

class DecorativeObject :
    public CGameObject
{
public:
    virtual void Render();
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

