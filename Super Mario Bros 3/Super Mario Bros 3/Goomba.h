#pragma once
#include "CGameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f
#define GOOMBA_GRAVITY 0.001f

#define GOOMBA_STATE_ALIVE 10
#define GOOMBA_STATE_FLATTEN 11
#define GOOMBA_STATE_DIE   66

#define GOOMBA_ANI_ALIVE   0
#define GOOMBA_ANI_FLATTEN     1

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 8

class Goomba :
    public CGameObject
{
protected:
    DWORD DieTime;
public:
    Goomba();
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void SetState(int state);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

