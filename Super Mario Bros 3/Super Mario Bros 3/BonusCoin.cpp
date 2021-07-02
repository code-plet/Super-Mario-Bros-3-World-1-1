#include "BonusCoin.h"

BonusCoin::BonusCoin() {

	setState(BONUSCOIN_STATE_SLEEP);
}

void BonusCoin::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {
	if (this->State == BONUSCOIN_STATE_RISING) {
		CGameObject::Update(dt);
		ay = BONUSCOIN_GRAVITY;
		y += dy;
		if (y > OG_y) setState(BONUSCOIN_STATE_CONSUMED);
	}
}

void BonusCoin::Render() {

	if (this->State != BONUSCOIN_STATE_CONSUMED) Animation_Set->at(BONUSCOIN_ANI)->Render(x, y);
}

void BonusCoin::setState(int State) {

	this->State = State;
	switch (State) {
	case BONUSCOIN_STATE_RISING:
		this->OG_y = this->y;
		vy = -BONUSCOIN_RISING_SPEED;
	default:
		break;

	}
}

void BonusCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom) {}