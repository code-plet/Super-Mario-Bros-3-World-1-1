#include "QuestionMarkBrick.h"
#include "GrowMushroom.h"
 
QuestionMarkBrick::QuestionMarkBrick() {

	this->State = QUESTION_MARK_STATE_ACTIVE;
}

void QuestionMarkBrick::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {
	if (this->State == QUESTION_MARK_STATE_DEPLOY) {
		for (int i = 0; i < coObjects->size(); i++) {
			float obj_x, obj_y;
			coObjects->at(i)->GetLocation(obj_x, obj_y);
			if (this->x == obj_x && this->y == obj_y) {
				coObjects->at(i)->setState(DEPLOY_POWER_UP);
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