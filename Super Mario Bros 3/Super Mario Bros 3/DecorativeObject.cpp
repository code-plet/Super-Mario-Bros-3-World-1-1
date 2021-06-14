#include "DecorativeObject.h"

void DecorativeObject::Render() {

	Animation_Set->at(DECORATIVEOBJECT_ANI)->Render(x, y);

}

void DecorativeObject::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}