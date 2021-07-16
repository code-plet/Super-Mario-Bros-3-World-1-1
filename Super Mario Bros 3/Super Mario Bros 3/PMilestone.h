#pragma once
#include "CGameObject.h"


#define PMILESTONE_STATE_HIDDEN      100
#define PMILESTONE_STATE_UP          101
#define PMILESTONE_STATE_PROVOKED    102
#define PMILESTONE_STATE_DOWN        103

#define PMILESTONE_HIDDEN_HEIGHT    16
#define PMILESTONE_HIDDEN_WIDTH     16
#define PMILESTONE_UP_HEIGHT 33
#define PMILESTONE_UP_WIDTH  16

#define PMILESTONE_ANI_UP       0
#define PMILESTONE_ANI_HIDDEN   1
#define PMILESTONE_ANI_DOWN     2

#define COIN_ANI_SET    61
#define BRICK_ANI_SET   21


class PMilestone :
    public CGameObject
{
protected:
    DWORD Triggered_time;

public:
    PMilestone();
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void setState(int state);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

