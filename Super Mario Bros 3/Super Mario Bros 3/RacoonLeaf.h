#pragma once
#include "CGameObject.h"

#define RACOONLEAF_GRAVITY        0.001f
#define RACOONLEAF_RISING_SPEED   0.01f
#define RACOONLEAF_MOVING_SPEED   0.05f

#define RACOONLEAF_STATE_SLEEP    10
#define RACOONLEAF_STATE_RISING   11
#define RACOONLEAF_STATE_MOVING   12
#define RACOONLEAF_STATE_CONSUMED 66

#define RACOONLEAF_BBOX_HEIGHT    14
#define RACOONLEAF_BBOX_WIDTH     16

#define RACOONLEAF_ANI_LEFT      0
#define RACOONLEAF_ANI_RIGHT     1

class RacoonLeaf :
    public CGameObject
{
public:
    RacoonLeaf();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void setState(int state);
};

