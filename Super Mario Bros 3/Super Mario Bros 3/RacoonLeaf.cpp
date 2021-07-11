#include "RacoonLeaf.h"

RacoonLeaf::RacoonLeaf() {

	setState(RACOONLEAF_STATE_SLEEP);
	nx = 1;
}

void RacoonLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	CGameObject::Update(dt);
	if (this->State != RACOONLEAF_STATE_SLEEP) {
		if (vy < RACOONLEAF_FALLING_SPEED) ay = RACOONLEAF_GRAVITY;
		else ay = 0;
		x += dx;
		y += dy;
		if (vy > 0 && this->State == RACOONLEAF_STATE_RISING) setState(RACOONLEAF_STATE_SLIDING_RIGHT);
		else if (this->State == RACOONLEAF_STATE_SLIDING_RIGHT) {
			if (vx > 0.15) 
				setState(RACOONLEAF_STATE_SLIDING_LEFT);
		}
		else if (this->State == RACOONLEAF_STATE_SLIDING_LEFT) {
			if (vx < -0.15) setState(RACOONLEAF_STATE_SLIDING_RIGHT);
		}
	}
}

void RacoonLeaf::Render() {
	if (vx > 0) {
		Animation_Set->at(RACOONLEAF_ANI_RIGHT)->Render(x, y);
	}else Animation_Set->at(RACOONLEAF_ANI_LEFT)->Render(x, y);
}

void RacoonLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	if (State != RACOONLEAF_STATE_SLEEP) {
		left = x;
		top = y;
		right = x + RACOONLEAF_BBOX_WIDTH;
		bottom = y + RACOONLEAF_BBOX_HEIGHT;
	}
}

void RacoonLeaf::setState	(int State) {
	this->State = State;
	switch (State) {
	case RACOONLEAF_STATE_RISING:
		vy = -RACOONLEAF_RISING_SPEED;
		vx = 0;
		break;
	case RACOONLEAF_STATE_SLIDING_RIGHT:
		nx = 1;
		ax = RACOONLEAF_SLIDING_SPEED;
		break;
	case RACOONLEAF_STATE_SLIDING_LEFT:
		nx = -1;
		ax = -RACOONLEAF_SLIDING_SPEED;
		break;
	default:
		break;
	}
}