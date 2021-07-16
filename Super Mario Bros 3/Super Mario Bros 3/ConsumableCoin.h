#pragma once
#include "CGameObject.h"

#define CONSUMABLE_COIN_STATE_ACTIVE    100
#define CONSUMABLE_COIN_STATE_CONSUMED  66

#define CONSUMABLE_COIN_HEIGHT  16
#define CONSUMABLE_COIN_WIDTH   14

  

class ConsumableCoin :
    public CGameObject
{
public:
    ConsumableCoin();
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void setState(int state);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

