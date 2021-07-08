#include "Fireball.h"

Fireball::Fireball(int direction) {
	switch (direction) {
	case DIRECTION_NORTHWEST_UPPER:
		vx = -FIREBALL_SPEED;
		vy = FIREBALL_SPEED * 2;
		break;
	case DIRECTION_NORTHWEST_LOWER:
		vx = -FIREBALL_SPEED * 2;
		vy = FIREBALL_SPEED;
		break;
	case DIRECTION_SOUTHWEST_UPPER:
		vx = -FIREBALL_SPEED * 2;
		vy = -FIREBALL_SPEED;
		break;
	case DIRECTION_SOUTHWEST_LOWER:
		vx = -FIREBALL_SPEED;
		vy = -FIREBALL_SPEED * 2;
		break;
	case DIRECTION_SOUTHEAST_UPPER:
		vx = FIREBALL_SPEED * 2;
		vy = -FIREBALL_SPEED;
		break;
	case DIRECTION_SOUTHEAST_LOWER:
		vx = FIREBALL_SPEED;
		vy = -FIREBALL_SPEED * 2;
		break;
	case DIRECTION_NORTHEAST_UPPER:
		vx = FIREBALL_SPEED;
		vy = FIREBALL_SPEED * 2;
		break;
	case DIRECTION_NORTHEAST_LOWER:
		vx = FIREBALL_SPEED * 2;
		vy = FIREBALL_SPEED;
		break;
	default:
		break;
	}
}

void Fireball::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {
	
	CGameObject::Update(dt);
	x += dx;
	y += dy;

}

void Fireball::Render() {
	Animation_Set->at(0)->Render(x, y);
}

void Fireball::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = this->x;
	top = this->y;
	right = this->x + 9;
	bottom = this->y + 9;

}