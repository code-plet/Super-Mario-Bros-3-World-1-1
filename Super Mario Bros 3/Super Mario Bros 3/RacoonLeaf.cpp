#include "RacoonLeaf.h"

RacoonLeaf::RacoonLeaf() {

	setState(RACOONLEAF_STATE_SLEEP);
	nx = 1;
}

void RacoonLeaf::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {
	
	CGameObject::Update(dt);
	if (this->State != RACOONLEAF_STATE_SLEEP) {
		ay -= RACOONLEAF_GRAVITY;
		x += dx;
		y += dy;
		if (vy > 0 && this->State == RACOONLEAF_STATE_RISING) setState(RACOONLEAF_STATE_MOVING);
		if (this->State == RACOONLEAF_STATE_MOVING) {
			if (abs(vx) > 0.2) {
				ax = -ax;
				nx = -nx;
			}
		}
	}

}

void RacoonLeaf::Render() {
	if (nx == 1) {
		Animation_Set->at(RACOONLEAF_ANI_LEFT)->Render(x, y);
	}else Animation_Set->at(RACOONLEAF_ANI_RIGHT)->Render(x, y);
}

void RacoonLeaf::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = x;
	top = y;
	right = x + RACOONLEAF_BBOX_WIDTH;
	bottom = y + RACOONLEAF_BBOX_HEIGHT;
}

void RacoonLeaf::setState	(int State) {
	this->State = State;
	switch (State) {
	case RACOONLEAF_STATE_RISING:
		vy = RACOONLEAF_RISING_SPEED;
		vx = 0;
		break;
	case RACOONLEAF_STATE_MOVING:
		ax = RACOONLEAF_MOVING_SPEED;
		break;
	default:
		break;
	}
}