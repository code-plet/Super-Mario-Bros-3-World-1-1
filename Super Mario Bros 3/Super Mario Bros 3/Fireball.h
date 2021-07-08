#pragma once
#include "CGameObject.h"

#define FIREBALL_SPEED  0.02f
#define FIREBALL_ANI    0

#define FIREBALL_ANIMATION_SET  105

class Fireball :
    public CGameObject
{
public:
    Fireball(int direction);
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();

    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
    
};

