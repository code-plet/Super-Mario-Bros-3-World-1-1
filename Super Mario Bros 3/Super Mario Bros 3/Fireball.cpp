#include "Fireball.h"

Fireball::Fireball(int direction) {
	if(direction == 0) //right top
	this->vx = FIREBALL_SPEED;
	this->vy = FIREBALL_SPEED;
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