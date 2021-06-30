#pragma once
#include "CollidableObstacle.h"

#define QUESTION_MARK_DEFLECT_SPEED 0.1f
#define QUESTION_MARK_GRAVITY      0.001f

#define QUESTION_MARK_STATE_ACTIVE 100
#define QUESTION_MARK_STATE_DEPLOY 101
#define QUESTION_MARK_STATE_EMPTY  102
#define DEPLOY_POWER_UP            11


#define QUESTION_MARK_ANI_ACTIVE   0
#define QUESTION_MARK_ANI_EMPTY    1


class QuestionMarkBrick :
    public CollidableObstacle
{
protected:
public:
   
    QuestionMarkBrick();
    void setState(int State);
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

