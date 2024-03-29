#include "Goomba.h"
#include "CollidableObstacle.h"

Goomba::Goomba() {

	setState(GOOMBA_STATE_ALIVE);
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


		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CollidableObstacle*>(e->obj)) {
				CollidableObstacle* CoObs = dynamic_cast<CollidableObstacle*>(e->obj);

				y += min_ty * dy + ny * 0.4f;
				if (ny != 0) { vy = 0; }

				x += min_tx * dx + nx * 0.4f;
				if (x < 10) x = 10;
				if (nx != 0 && !CoObs->GetTopOnly())
				{
					vx = -vx;
				}
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
}

void Goomba::Render() {

	int ani;
	if (State == GOOMBA_STATE_ALIVE) ani = GOOMBA_ANI_ALIVE;
	else if (State == GOOMBA_STATE_FLATTEN) {
		DWORD CurrentDieTime = GetTickCount();
		if (CurrentDieTime - this->DieTime > 200) this->setState(GOOMBA_STATE_DIE);
		ani = GOOMBA_ANI_FLATTEN;
	}
	Animation_Set->at(ani)->Render(x, y);
}

void Goomba::setState(int State) {

	this->State = State;
	switch (State)
	{
	case GOOMBA_STATE_ALIVE:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_FLATTEN:
		y += 7;    //Flatten Goomba is shorter. 
		this->DieTime = GetTickCount();
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_DIE:
		break;
	default:
		break;
	}
}

void Goomba::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	if (this->State == GOOMBA_STATE_FLATTEN) {
		left = x;
		top = y;

		right = x + GOOMBA_BBOX_WIDTH;
		bottom = y + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else {
		left = x;
		top = y;

		right = x + GOOMBA_BBOX_WIDTH;
		bottom = y + GOOMBA_BBOX_HEIGHT;
	}

}