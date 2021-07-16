#pragma once
#include "CollidableObstacle.h"
#include "PowerUp.h"

#define QUESTION_MARK_DEFLECT_SPEED 0.1f
#define QUESTION_MARK_GRAVITY      0.001f

#define COIN_ANI_SET        
#define MUSHROOM_ANI_SET    
#define RACOONLEAF_ANI_SET  

#define QUESTION_MARK_STATE_ACTIVE 100
#define QUESTION_MARK_STATE_DEPLOY 101
#define QUESTION_MARK_STATE_EMPTY  102
#define DEPLOY_POWER_UP            11
#define DELETE_POWER_UP            66


#define QUESTION_MARK_ANI_ACTIVE   0
#define QUESTION_MARK_ANI_EMPTY    1


class QuestionMarkBrick :
    public CollidableObstacle
{
protected:
    PowerUp* content=NULL;
    int type; // 0 = coin; 1 = P-up;
public:
   
    QuestionMarkBrick();
    void setState(int State);
    void Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects = NULL);
    void Render();
    void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

