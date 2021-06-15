#pragma once
#include "CollidableObstacle.h"

#define QUESTION_MARK_STATE_ACTIVE 100
#define QUESTION_MARK_STATE_EMPTY  101

#define QUESTION_MARK_ANI_ACTIVE   0
#define QUESTION_MARK_ANI_EMPTY    1


class QuestionMarkBrick :
    public CollidableObstacle
{
public:
   
    QuestionMarkBrick();
    void SetState();
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void GetBoundingBox();
};

