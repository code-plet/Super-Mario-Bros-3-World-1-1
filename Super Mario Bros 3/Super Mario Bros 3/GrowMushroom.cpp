#include <stdlib.h>    

#include "GrowMushroom.h"
#include "CollidableObstacle.h"
GrowMushroom::GrowMushroom() {

	setState(GROWMUSHROOM_STATE_SLEEP);

}

void GrowMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);
	if (this->State == GROWMUSHROOM_STATE_RISING) {
		if (OG_y - this->y > 16) setState(GROWMUSHROOM_STATE_MOVING);
		else {
			y += dy;
		}
	}
	else if (this->State == GROWMUSHROOM_STATE_MOVING) {
		ay = GROWMUSHROOM_GRAVITY;

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
}

void GrowMushroom::Render() {
	Animation_Set->at(0)->Render(x, y);
}

void GrowMushroom::setState(int state) {
	this->State = state;
	switch (State)
	{
	case GROWMUSHROOM_STATE_RISING:
		this->OG_y = this->y;
		vy = -GROWMUSHROOM_RISING_SPEED;
		break;
	case GROWMUSHROOM_STATE_MOVING:
	{
		byte random = GetTickCount();
		if (random % 2 == 0) vx = GROWMUSHROOM_MOVING_SPEED;
		else vx = -GROWMUSHROOM_MOVING_SPEED;
	}
		break;
	default:
		break;
	}
}

void GrowMushroom::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	if (this->State != GROWMUSHROOM_STATE_SLEEP) {
		left = x;
		top = y;
		right = x + GROWMUSHROOM_BBOX_WIDTH;
		bottom = y + GROWMUSHROOM_BBOX_HEIGHT;
	}
}
