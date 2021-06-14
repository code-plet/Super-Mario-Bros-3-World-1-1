#include "CollidableObstacle.h"

void CollidableObstacle::Render() {

	Animation_Set->at(OBSTACLE_ANI)->Render(x, y);

}

void CollidableObstacle::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = x;
	top = y;
	right = x + Width;
	bottom = y + Height;
}