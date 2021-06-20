#include "Goomba.h"

Goomba::Goomba() {

	SetState(GOOMBA_STATE_ALIVE);
}

void Goomba::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);

	ay = GOOMBA_GRAVITY;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {

		x += dx;
		y += dy;
	}
	else {
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0;
		float rdy = 0;

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		// block every object first!
		x += min_tx * dx + nx * 0.4f;

		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) { vx = 0; }
		if (ny != 0) { vy = 0; }



		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void Goomba::Render() {

	int ani;
	if (State == GOOMBA_STATE_ALIVE) ani = GOOMBA_ANI_ALIVE;
	else ani = GOOMBA_ANI_DIE;
	Animation_Set->at(ani)->Render(x, y);
}

void Goomba::SetState(int State) {

	this->State = State;
	switch (State)
	{
	case GOOMBA_STATE_ALIVE:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_DIE:
		vx = 0;
		vy = 0;
		break;
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