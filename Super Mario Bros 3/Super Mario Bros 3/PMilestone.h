#pragma once
#include "CGameObject.h"
class PMilestone :
    public CGameObject
{

    PMilestone();
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void setState(int state);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

