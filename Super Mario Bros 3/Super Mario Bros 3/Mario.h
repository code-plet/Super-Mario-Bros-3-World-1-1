#pragma once
#include "CGameObject.h"

#define MARIO_JUMP_SPEED         0.4f
#define MARIO_WALKING_SPEED      0.15f
#define MARIO_SPRINTING_SPEED    0.23f
#define MARIO_GRAVITY            0.001f
#define MARIO_FISSION            0.0002f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f

#define MARIO_LEVEL_SMALL       0
#define MARIO_LEVEL_BIG         1
#define MARIO_LEVEL_RACOON      2

#define MARIO_STATE_IDLE          200
#define MARIO_STATE_JUMP          201
#define MARIO_STATE_DIE           202
#define MARIO_STATE_WALK_LEFT     203
#define MARIO_STATE_WALK_RIGHT    204
#define MARIO_STATE_BREAK_RIGHT   205
#define MARIO_STATE_BREAK_LEFT    206
#define MARIO_STATE_SPRINT_RIGHT  207
#define MARIO_STATE_SPRINT_LEFT   208
#define MARIO_STATE_DIVE          209

#define MARIO_ANI_SMALL_IDLE_RIGHT   24
#define MARIO_ANI_SMALL_IDLE_LEFT    25
#define MARIO_ANI_SMALL_WALK_RIGHT   26
#define MARIO_ANI_SMALL_WALK_LEFT    27
#define MARIO_ANI_SMALL_BRAKE_LEFT   28
#define MARIO_ANI_SMALL_BRAKE_RIGHT  29
#define MARIO_ANI_SMALL_JUMP_RIGHT   30
#define MARIO_ANI_SMALL_JUMP_LEFT    31
#define MARIO_ANI_SMALL_SPRINT_RIGHT 32
#define MARIO_ANI_SMALL_SPRINT_LEFT  33

#define MARIO_ANI_BIG_IDLE_RIGHT   0
#define MARIO_ANI_BIG_IDLE_LEFT    1
#define MARIO_ANI_BIG_WALK_RIGHT   2
#define MARIO_ANI_BIG_WALK_LEFT    3
#define MARIO_ANI_BIG_BRAKE_RIGHT  4
#define MARIO_ANI_BIG_BRAKE_LEFT   5
#define MARIO_ANI_BIG_JUMP_RIGHT   6
#define MARIO_ANI_BIG_JUMP_LEFT    7
#define MARIO_ANI_BIG_DIVE_RIGHT   8
#define MARIO_ANI_BIG_DIVE_LEFT    9
#define MARIO_ANI_BIG_SPRINT_RIGHT 10
#define MARIO_ANI_BIG_SPRINT_LEFT  11

#define MARIO_ANI_RACOON_IDLE_RIGHT   12
#define MARIO_ANI_RACOON_IDLE_LEFT    13
#define MARIO_ANI_RACOON_WALK_RIGHT   14
#define MARIO_ANI_RACOON_WALK_LEFT    15
#define MARIO_ANI_RACOON_BRAKE_RIGHT  16
#define MARIO_ANI_RACOON_BRAKE_LEFT   17
#define MARIO_ANI_RACOON_JUMP_RIGHT   18
#define MARIO_ANI_RACOON_JUMP_LEFT    19
#define MARIO_ANI_RACOON_DIVE_RIGHT   20
#define MARIO_ANI_RACOON_DIVE_LEFT    21
#define MARIO_ANI_RACOON_SPRINT_RIGHT 22
#define MARIO_ANI_RACOON_SPRINT_LEFT  23

#define MARIO_SMALL_BBOX_WIDTH  15
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27
#define MARIO_BIG_DIVE_BBOX_WIDTH 15
#define MARIO_BIG_DIVE_BBOX_HEIGHT 18

#define MARIO_RACOON_BBOX_WIDTH  21
#define MARIO_RACOON_BBOX_HEIGHT 28
#define MARIO_RACOON_DIVE_BBOX_WIDTH 21
#define MARIO_RACOON_DIVE_BBOX_HEIGHT 18

class Mario :
    public CGameObject
{
protected:
    int Level;
public:

    Mario();
    void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects);
    void Render();
    void Reset() { this->x = 160; this->y = 155; }

    void setState(int State);
    void setLevel(int level);

    int GetLevel() { return this->Level; }
    virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};