#pragma once
#include "CGameObject.h"
#include "PowerUp.h"

#define BONUSCOIN_STATE_SLEEP    10
#define BONUSCOIN_STATE_RISING   11
#define BONUSCOIN_STATE_CONSUMED 66

#define BONUSCOIN_RISING_SPEED  0.3f
#define BONUSCOIN_GRAVITY       0.001f

#define BONUSCOIN_ANI   0

class BonusCoin :
    public PowerUp
{
protected:
    float OG_y;
public:

    BonusCoin();
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void setState(int State);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

