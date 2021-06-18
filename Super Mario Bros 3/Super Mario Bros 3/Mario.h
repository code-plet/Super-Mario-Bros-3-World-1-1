#pragma once
#include "CGameObject.h"

#define MARIO_JUMP_SPEED       0.4f
#define MARIO_WALKING_SPEED    0.15f
#define MARIO_GRAVITY          0.001f
#define MARIO_FISSION          0.0002f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f

#define MARIO_STATE_IDLE        100
#define MARIO_STATE_JUMP        101
#define MARIO_STATE_DIE         102
#define MARIO_STATE_WALK_LEFT   110
#define MARIO_STATE_WALK_RIGHT  111
#define MARIO_STATE_BREAK_RIGHT 113
#define MARIO_STATE_BREAK_LEFT  114
#define MARIO_STATE_DIVE        120    

#define MARIO_ANI_IDLE_RIGHT   0
#define MARIO_ANI_IDLE_LEFT    1
#define MARIO_ANI_WALK_RIGHT   4
#define MARIO_ANI_WALK_LEFT    5
#define MARIO_ANI_BRAKE_RIGHT  8
#define MARIO_ANI_BRAKE_LEFT   9
#define MARIO_ANI_JUMP_RIGHT   10
#define MARIO_ANI_JUMP_LEFT    11
#define MARIO_ANI_DIVE_RIGHT   12
#define MARIO_ANI_DIVE_LEFT    13

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27


class Mario :
    public CGameObject
{
public:

    Mario() { nx = 1; }
    void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    void Render();
    void Reset() { this->x = 160; this->y = 155; }

    void setState(int State);

    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

