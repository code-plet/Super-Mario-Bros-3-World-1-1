#include "Brick.h"

void Brick::Render() {

	Animation_Set->at(BRICK_ANI)->Render(x, y);
	RenderBoundingBox();

}

void Brick::GetBoundingBox(float& left, float& top, float& right, float& bottom) {
	left = this->x;
	top = this->y;

	right = x + 17;
	bottom = y + 17;
}
