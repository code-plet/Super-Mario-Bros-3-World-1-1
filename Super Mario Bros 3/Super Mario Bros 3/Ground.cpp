#include "Ground.h"

void Ground::Render() {

	Animation_Set->at(GROUND_ANI)->Render(x, y);
}

void Ground::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = this->x;
	top = this->y;
	right = x + 624;
	bottom = y + 16;
}