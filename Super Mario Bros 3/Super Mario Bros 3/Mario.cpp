#include "Mario.h"
#include "Goomba.h"
#include "QuestionMarkBrick.h"
#include "CollidableObstacle.h"

vector<LPCOLLISIONEVENT> coEvents;
vector<LPCOLLISIONEVENT> coEventsResult;

void Mario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt); // Uses ax,ay to calculate vx, vy 

	ay = MARIO_GRAVITY;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0) {

		x += dx;
		y += dy;
		if (x < 10) x = 10;
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
		/*x += min_tx * dx + nx * 0.4f;
		if (x < 10) x = 10;

		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) { vx = 0; }
		if (ny != 0) { vy = 0; }*/



		//
		// Collision logic with other objects
		//
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<Goomba*>(e->obj)) // if e->obj is Goomba 
			{
				Goomba* goomba = dynamic_cast<Goomba*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					Reset();
				}
			}
			else if (dynamic_cast<QuestionMarkBrick*>(e->obj)) {

				x += min_tx * dx + nx * 0.4f;
				if (x < 10) x = 10;

				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) { vx = 0; }
				if (ny != 0) { vy = 0; }

				QuestionMarkBrick* QMB = dynamic_cast<QuestionMarkBrick*>(e->obj);
				if (e->ny > 0 && QMB->GetState() == QUESTION_MARK_STATE_ACTIVE) {
						QMB->setState(QUESTION_MARK_STATE_EMPTY);
				}
			}
			else if (dynamic_cast<CollidableObstacle*>(e->obj)) {
				CollidableObstacle* CoObs = dynamic_cast<CollidableObstacle*>(e->obj);
				if (CoObs->GetTopOnly() && ( e->ny > 0 || e->nx!=0) ) {
					if (e->ny > 0) y += dy;
					if (e->nx != 0) { 
						x += dx; 
						if (x < 10) x = 10; 
					}
				}
				else {
					x += min_tx * dx + nx * 0.4f;
					if (x < 10) x = 10;

					y += min_ty * dy + ny * 0.4f;

					if (nx != 0) { vx = 0; }
					if (ny != 0) { vy = 0; }
				}
			}

		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::Render() {

	int ani = -1;
	if (vy < 0 || vy> 0.017 ) if (nx == 1) ani = MARIO_ANI_JUMP_RIGHT;
	else ani = MARIO_ANI_JUMP_LEFT;
	else if (State == MARIO_STATE_DIVE) if (nx == 1) ani = MARIO_ANI_DIVE_RIGHT;
	else ani = MARIO_ANI_DIVE_LEFT;
	else if (vx > 0) if (nx == -1) ani = MARIO_ANI_BRAKE_RIGHT;
	else ani = MARIO_ANI_WALK_RIGHT; 
	else if (vx < 0) if (nx == 1) ani = MARIO_ANI_BRAKE_LEFT;
	else ani = MARIO_ANI_WALK_LEFT;
	else if (nx == 1) ani = MARIO_ANI_IDLE_RIGHT;
	else ani = MARIO_ANI_IDLE_LEFT;

	int alpha = 255;
	DebugOut(L"v_x, v_y : %f, %f ", vx,vy);
	Animation_Set->at(ani)->Render(x, y, alpha);

	RenderBoundingBox();

}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x;
	top = y;

	right = x + MARIO_BIG_BBOX_WIDTH;
	bottom = y + MARIO_BIG_BBOX_HEIGHT;

}

void Mario::setState(int State){

	switch (State)
	{
	case MARIO_STATE_JUMP:

 		if (vy >= 0 && vy< 0.017) vy = -MARIO_JUMP_SPEED;
		break;

	case MARIO_STATE_WALK_RIGHT:

		if (vx <= MARIO_WALKING_SPEED) ax = MARIO_FISSION;
		else ax = 0;
		nx = 1;
		break;

	case MARIO_STATE_WALK_LEFT:

		if (vx >= -MARIO_WALKING_SPEED) ax = -MARIO_FISSION;
		else ax = 0;
		nx = -1;
		break;

	case MARIO_STATE_BREAK_RIGHT:

		nx = 1;
		ax = MARIO_FISSION * 2.4;
		break;

	case MARIO_STATE_BREAK_LEFT:

		nx = -1;
		ax = -MARIO_FISSION * 2.4;
		break;

	case MARIO_STATE_IDLE:

		if (vx > 0) {
			ax = -MARIO_FISSION;
			if (vx < MARIO_FISSION * 1.5 * dt) { vx = 0; ax = 0; }
		}			
		if (vx < 0) {
			ax = MARIO_FISSION;
			if (vx > -MARIO_FISSION * 1.5 * dt) { vx = 0; ax = 0; }

		}
		break;
	case MARIO_STATE_DIVE:

		if (vx > 0) {
			ax = -MARIO_FISSION;
			if (vx < MARIO_FISSION * 1.5 * dt) { vx = 0; ax = 0; }
		}
		if (vx < 0) {
			ax = MARIO_FISSION;
			if (vx > -MARIO_FISSION * 1.5 * dt) { vx = 0; ax = 0; }
		}
		break;
	default:

		break;
	}

	CGameObject::setState(State);
}