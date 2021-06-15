#include "Goomba.h"

Goomba::Goomba() {

	SetState(GOOMBA_STATE_ALIVE);
}

void Goomba::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);
	x += dx; 
	y += dy; 
}

void Goomba::Render() {

	int ani;
	if (State = GOOMBA_STATE_ALIVE) ani = GOOMBA_ANI_ALIVE;
	else ani = GOOMBA_ANI_DIE;
	Animation_Set->at(ani)->Render(x, y);
}

void Goomba::SetState(int State) {

	switch (State)
	{
	case GOOMBA_STATE_ALIVE:
		vx = -GOOMBA_WALKING_SPEED;
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
	default:
		break;
	}
}

void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	left = x;
	top = y;
	right = x + GOOMBA_BBOX_WIDTH;

	if (State == GOOMBA_STATE_DIE)
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		bottom = y + GOOMBA_BBOX_HEIGHT;

}