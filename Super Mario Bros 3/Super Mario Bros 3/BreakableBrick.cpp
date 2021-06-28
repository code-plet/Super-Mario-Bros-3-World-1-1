#include "BreakableBrick.h"

void BreakableBrick::Render() {

	int ani;
	if (State == BRICK_STATE_ACTIVE) {
		ani = BRICK_ANI_ACTIVE;
		Animation_Set->at(ani)->Render(x, y);
	}
}

void BreakableBrick::setState(int State) {

	this->State = State;
	switch (State)
	{
	case BRICK_STATE_ACTIVE:
		break;
	case BRICK_STATE_BROKEN:
		break;
	default:
		break;
	}

}

void BreakableBrick::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = x;
	top = y;
	right = x + this->Width;
	bottom = y + this->Height;
}