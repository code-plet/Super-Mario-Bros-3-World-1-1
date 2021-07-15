#pragma once
#include "CGameObject.h"
#include "PowerUp.h"

#define GROWMUSHROOM_GRAVITY        0.001f
#define GROWMUSHROOM_RISING_SPEED   0.01f
#define GROWMUSHROOM_MOVING_SPEED   0.05f

#define GROWMUSHROOM_STATE_SLEEP    10
#define GROWMUSHROOM_STATE_RISING   11
#define GROWMUSHROOM_STATE_MOVING   12
#define GROWMUSHROOM_STATE_CONSUMED 66

#define GROWMUSHROOM_BBOX_HEIGHT    16
#define GROWMUSHROOM_BBOX_WIDTH     16

#define GROWMUSHROOM_ANI 0

class GrowMushroom :
    public PowerUp
{
protected:
    int  OG_y;
public:

    GrowMushroom(); 
    void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void setState(int state);
};

