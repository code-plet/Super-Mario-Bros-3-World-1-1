#pragma once
#include "CGameObject.h"
#include "Animation.h"

#define BRICK_BBOX_HEIGHT 17
#define BRICK_BBOX_WIDTH  17

#define BRICK_ANI 0

class Brick :
    public CGameObject
{
     virtual void Render();
     virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

