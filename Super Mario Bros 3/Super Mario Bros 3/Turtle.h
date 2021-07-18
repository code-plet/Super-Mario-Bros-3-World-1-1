#pragma once
#include "CGameObject.h"

#define TURTLE_WALKING_SPEED    0.03f
#define TURTLE_GRAVITY  0.002f
#define TURTLE_JUMP     0.01f
#define TURTLE_SPINNING_SPEED   0.15f

#define TURTLE_GREEN    0
#define TURTLE_RED      1

#define TURTLE_STATE_WINGED            0
#define TURTLE_STATE_ONFOOT            1
#define TURTLE_STATE_TURTLED           2
#define TURTLE_STATE_FLIPPED           3
#define TURTLE_STATE_SPINNING          4
#define TURTLE_STATE_FLIPPED_SPINNING  5
#define TURTLE_STATE_DIED              66

#define TURTLE_GREEN_ANI_WINGED_LEFT            0
#define TURTLE_GREEN_ANI_WINGED_RIGHT           1
#define TURTLE_GREEN_ANI_ONFOOT_LEFT            2
#define TURTLE_GREEN_ANI_ONFOOT_RIGHT           3
#define TURTLE_GREEN_ANI_TURTLED                4
#define TURTLE_GREEN_ANI_FLIPPED                5
#define TURTLE_GREEN_ANI_SPINNING_LEFT          6
#define TURTLE_GREEN_ANI_SPINNING_RIGHT         7
#define TURTLE_GREEN_ANI_FLIPPED_SPINNING_LEFT  8
#define TURTLE_GREEN_ANI_FLIPPED_SPINNING_RIGHT 9

#define TURTLE_RED_ANI_WINGED_LEFT              10
#define TURTLE_RED_ANI_WINGED_RIGHT             11
#define TURTLE_RED_ANI_ONFOOT_LEFT              12
#define TURTLE_RED_ANI_ONFOOT_RIGHT             13
#define TURTLE_RED_ANI_TURTLED                  14
#define TURTLE_RED_ANI_FLIPPED                  15
#define TURTLE_RED_ANI_SPINNING_LEFT            16
#define TURTLE_RED_ANI_SPINNING_RIGHT           17
#define TURTLE_RED_ANI_FLIPPED_SPINNING_LEFT    18
#define TURTLE_RED_ANI_FLIPPED_SPINNING_RIGHT   19

#define TURTLE_WINGED_HEIGHT    36
#define TURTLE_WINGED_WIDTH     16
#define TURTLE_ONFOOT_HEIGHT    26
#define TURTLE_ONFOOT_WIDTH     16
#define TURTLE_TURTLED_HEIGHT   16
#define TURTLE_TURTLED_WIDTH    16

class Turtle :
    public CGameObject
{
protected:

    int color; // 0: red; 1: green;
    bool patrol;    // true if turtle follows a certain patrol route
    float pointA_x, pointA_y, pointB_x, pointB_y; //Start and end if turtle follows a certain route


public:

    Turtle();
    Turtle(int startingstate, int color);
    Turtle(int startingstate, int color, float pointA_x, float pointA_y, float pointB_x, float pointB_y);

    void setPatrol(bool patrol) { this->patrol = patrol; }

    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void setState(int state);
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);

};

