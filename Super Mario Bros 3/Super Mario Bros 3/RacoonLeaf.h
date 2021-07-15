#pragma once
#include "CGameObject.h"
#include "PowerUp.h"

#define RACOONLEAF_GRAVITY        0.0005f
#define RACOONLEAF_RISING_SPEED   0.2f
#define RACOONLEAF_FALLING_SPEED   0.02f
#define RACOONLEAF_SLIDING_SPEED   0.0006f


#define RACOONLEAF_STATE_SLEEP          10
#define RACOONLEAF_STATE_RISING         11
#define RACOONLEAF_STATE_SLIDING_LEFT   12
#define RACOONLEAF_STATE_SLIDING_RIGHT  13
#define RACOONLEAF_STATE_CONSUMED       66

#define RACOONLEAF_BBOX_HEIGHT    14
#define RACOONLEAF_BBOX_WIDTH     16

#define RACOONLEAF_ANI_LEFT      0
#define RACOONLEAF_ANI_RIGHT     1

class RacoonLeaf :
    public PowerUp
{
public:
    RacoonLeaf();
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void setState(int state);
};

