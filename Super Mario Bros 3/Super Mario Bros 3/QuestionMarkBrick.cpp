#include "QuestionMarkBrick.h"
 
QuestionMarkBrick::QuestionMarkBrick() {

	this->State = QUESTION_MARK_STATE_ACTIVE;
}

void QuestionMarkBrick::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {

	
}

void QuestionMarkBrick::Render() {

	int ani;
	if (State == QUESTION_MARK_STATE_ACTIVE) ani = QUESTION_MARK_ANI_ACTIVE;
	else ani = QUESTION_MARK_ANI_EMPTY;
	Animation_Set->at(ani)->Render(x, y);
}

void QuestionMarkBrick::setState(int State) {

	this->State = State;
}

void QuestionMarkBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = x;
	top = y;
	right = x + this->Width;
	bottom = y + this->Height;
}