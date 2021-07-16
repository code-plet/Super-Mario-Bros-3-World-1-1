#include "QuestionMarkBrick.h"
#include "BonusCoin.h"
#include "GrowMushroom.h"
#include "RacoonLeaf.h"
#include "Mario.h"
 
QuestionMarkBrick::QuestionMarkBrick() {

	this->State = QUESTION_MARK_STATE_ACTIVE;
}

void QuestionMarkBrick::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {
	if (this->State == QUESTION_MARK_STATE_DEPLOY) {
		int mario_Level = Cgame::GetInstance()->GetCurrentScene()->GetPlayer()->GetLevel();
		for (int i = 0; i < coObjects->size(); i++) {
			float obj_x, obj_y;
			coObjects->at(i)->GetLocation(obj_x, obj_y);
			if (this->x == obj_x && this->y == obj_y && !dynamic_cast<QuestionMarkBrick*>(coObjects->at(i))) {
				if (dynamic_cast<BonusCoin*>(coObjects->at(i))) {
					coObjects->at(i)->setState(DEPLOY_POWER_UP);
				}
				else if (mario_Level == MARIO_LEVEL_SMALL) {
					if (dynamic_cast<GrowMushroom*>(coObjects->at(i))) {
						coObjects->at(i)->setState(DEPLOY_POWER_UP);
					}
					else coObjects->at(i)->setState(DELETE_POWER_UP);
				}
				else if (mario_Level == MARIO_LEVEL_BIG || mario_Level == MARIO_LEVEL_RACOON) {
					if (dynamic_cast<RacoonLeaf*>(coObjects->at(i))) {
						coObjects->at(i)->setState(DEPLOY_POWER_UP);
					}
					else coObjects->at(i)->setState(DELETE_POWER_UP);
				}

			}
		}
		this->setState(QUESTION_MARK_STATE_EMPTY);
	}
	
}

void QuestionMarkBrick::Render() {

	int ani;
	if (State == QUESTION_MARK_STATE_ACTIVE) ani = QUESTION_MARK_ANI_ACTIVE;
	else ani = QUESTION_MARK_ANI_EMPTY;
	Animation_Set->at(ani)->Render(x, y);
}

void QuestionMarkBrick::setState(int State) {

	this->State = State;
	switch (State)
	{
	case QUESTION_MARK_STATE_EMPTY:
		break;
	case QUESTION_MARK_STATE_DEPLOY:
		break;
	}
}

void QuestionMarkBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = x;
	top = y;
	right = x + this->Width;
	bottom = y + this->Height;
}