#pragma once
#include "CGameObject.h"

#define VENUSFIRETRAP_SPEED 0.03f
#define VENUSFIRETRAP_WAIT_TIME  1400 

#define VENUSFIRETRAP_HEIGHT    32
#define VENUSFIRETRAP_WIDTH     16

#define VENUSFIRETRAP_STATE_SLEEP   100     // Sleeps in the tunnel, ready for whenever Mario is in range
#define VENUSFIRETRAP_STATE_DEPLOY  101     // Rises up until hitting peak height
#define VENUSFIRETRAP_STATE_FIRE    102     // FireTrap takes a moment to aim and fire
#define VENUSFIRETRAP_STATE_FIRED   103     // Waits a while before going down
#define VENUSFIRETRAP_STATE_HIDE    104     // Goes down and wait for <cooldown time>
#define VENUSFIRETRAP_STATE_DIE     66

#define VENUSFIRETRAP_ANI_RED_DEPLOYING_DOWN_RIGHT        0
#define VENUSFIRETRAP_ANI_RED_DEPLOYING_DOWN_LEFT         1
#define VENUSFIRETRAP_ANI_RED_DEPLOYING_UP_RIGHT          2
#define VENUSFIRETRAP_ANI_RED_DEPLOYING_UP_LEFT           3
#define VENUSFIRETRAP_ANI_RED_FIRE_DOWN_RIGHT             4
#define VENUSFIRETRAP_ANI_RED_FIRE_DOWN_LEFT              5
#define VENUSFIRETRAP_ANI_RED_FIRE_UP_RIGHT               6
#define VENUSFIRETRAP_ANI_RED_FIRE_UP_LEFT                7
#define VENUSFIRETRAP_ANI_GREEN_DEPLOYING_DOWN_RIGHT      8
#define VENUSFIRETRAP_ANI_GREEN_DEPLOYING_DOWN_LEFT       9
#define VENUSFIRETRAP_ANI_GREEN_DEPLOYING_UP_RIGHT        10
#define VENUSFIRETRAP_ANI_GREEN_DEPLOYING_UP_LEFT         11
#define VENUSFIRETRAP_ANI_GREEN_FIRE_DOWN_RIGHT           12
#define VENUSFIRETRAP_ANI_GREEN_FIRE_DOWN_LEFT            13
#define VENUSFIRETRAP_ANI_GREEN_FIRE_UP_RIGHT             14
#define VENUSFIRETRAP_ANI_GREEN_FIRE_UP_LEFT              15

class VenusFireTrap :
    public CGameObject
{
protected: 

    float OG_y = 0;   // calculate peak height
    DWORD Ready_time; // to calculate when to fire (Cooldown_time = this*2.5)
    int color;        // color 0: red; 1:green

public:

    VenusFireTrap(int color);

    // Inherited via CGameObject
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();

    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    void setState(int State);

};

