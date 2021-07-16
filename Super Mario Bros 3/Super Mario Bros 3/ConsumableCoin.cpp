#include "ConsumableCoin.h"

ConsumableCoin::ConsumableCoin() {
	this->setState(CONSUMABLE_COIN_STATE_ACTIVE);
}

void ConsumableCoin::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {

}

void ConsumableCoin::Render() {
	if (this->State == CONSUMABLE_COIN_STATE_ACTIVE) this->Animation_Set->at(0)->Render(x, y);
}

void ConsumableCoin::setState(int State) {
	this->State = State;
}

void ConsumableCoin::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = x;
	top = y;
	right = x + CONSUMABLE_COIN_WIDTH;
	bottom = y + CONSUMABLE_COIN_HEIGHT;
}