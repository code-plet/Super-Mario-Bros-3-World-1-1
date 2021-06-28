#include "CollidableObstacle.h"

void CollidableObstacle::Render() {

	Animation_Set->at(OBSTACLE_ANI)->Render(x, y);

}

void CollidableObstacle::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	if (TopOnly) {

		left = x;
		top = y;
		right = x + Width;
		bottom = y + 1;
	}
	else {

		left = x;
		top = y;
		right = x + Width;
		bottom = y + Height;
	}
}