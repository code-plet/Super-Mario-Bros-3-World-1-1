#include "Mario.h"
#include "Goomba.h"
#include "QuestionMarkBrick.h"
#include "CollidableObstacle.h"
#include "BreakableBrick.h"
#include "GrowMushroom.h"
#include "VenusFireTrap.h"
#include "Fireball.h"
#include "RacoonLeaf.h"
#include "Turtle.h"
#include "ConsumableCoin.h"
#include "PMilestone.h"

vector<LPCOLLISIONEVENT> coEvents;
vector<LPCOLLISIONEVENT> coEventsResult;

Mario::Mario() {

	nx = 1;
	this->Level=MARIO_LEVEL_SMALL;
}

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
					if (goomba->GetState() != GOOMBA_STATE_FLATTEN)
					{
						goomba->setState(GOOMBA_STATE_FLATTEN);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					Reset();
				}
			}
			else if (dynamic_cast<PMilestone*>(e->obj)) {
				PMilestone* obj = dynamic_cast<PMilestone*>(e->obj);
				x += min_tx * dx + nx * 0.4f;
				if (x < 10) x = 10;
				if (nx != 0) vx = 0;
				y += min_ty * dy + ny * 0.4f;
				if (ny != 0) { vy = 0; }
				if (ny > 0 && obj->GetState() == PMILESTONE_STATE_HIDDEN) obj->setState(PMILESTONE_STATE_UP);
				if (ny < 0 && obj->GetState() == PMILESTONE_STATE_UP) obj->setState(PMILESTONE_STATE_PROVOKED);
			}
	 		else if (dynamic_cast<QuestionMarkBrick*>(e->obj)) {

				//If collides beneath the brick, give item.
				QuestionMarkBrick* QMB = dynamic_cast<QuestionMarkBrick*>(e->obj);
				if (e->ny > 0 && QMB->GetState() == QUESTION_MARK_STATE_ACTIVE) {
						QMB->setState(QUESTION_MARK_STATE_DEPLOY);
						x += min_tx * dx + nx * 0.4f;
						if (x < 10) x = 10;
						if (nx != 0) vx = 0;
						y += min_ty * dy + ny * 0.4f;
						if (ny != 0) { vy = 0; }
				}
				else {
					x += min_tx * dx + nx * 0.4f;
					if (x < 10) x = 10;
					if (nx != 0) vx = 0;
					y += min_ty * dy + ny * 0.4f;
					if (ny != 0) { vy = 0; }
				}
			}
			else if (dynamic_cast<ConsumableCoin*>(e->obj)) {
				ConsumableCoin* coin = dynamic_cast<ConsumableCoin*>(e->obj);
				coin->setState(CONSUMABLE_COIN_STATE_CONSUMED);
			}
			else if (dynamic_cast<BreakableBrick*>(e->obj)) {
				BreakableBrick* CoObs = dynamic_cast<BreakableBrick*>(e->obj);
				if (e->ny > 0) CoObs->setState(BRICK_STATE_BROKEN);
				x += min_tx * dx + nx * 0.4f;
				if (x < 10) x = 10;

				y += min_ty * dy + ny * 0.4f;

				if (nx != 0) { vx = 0; }
				if (ny != 0) { vy = 0; }
			}
			else if (dynamic_cast<GrowMushroom*>(e->obj)) {
				GrowMushroom* coObs = dynamic_cast<GrowMushroom*>(e->obj);
				if (this->Level == MARIO_LEVEL_SMALL) this->setLevel(MARIO_LEVEL_BIG);
				coObs->setState(GROWMUSHROOM_STATE_CONSUMED);
			}
			else if (dynamic_cast<VenusFireTrap*>(e->obj)) {
				if (this->Level == MARIO_LEVEL_RACOON) this->setLevel(MARIO_LEVEL_BIG);
				if (this->Level == MARIO_LEVEL_BIG) this->setLevel(MARIO_LEVEL_SMALL);
				else if (this->Level == MARIO_LEVEL_SMALL) this->Reset();
			}
			else if (dynamic_cast<RacoonLeaf*>(e->obj)) {
				RacoonLeaf* coObs = dynamic_cast<RacoonLeaf*>(e->obj);
				if (this->Level != MARIO_LEVEL_RACOON) this->setLevel(MARIO_LEVEL_RACOON);
				coObs->setState(GROWMUSHROOM_STATE_CONSUMED);
			}
			else if (dynamic_cast<Fireball*>(e->obj)) {
			}
			else if (dynamic_cast<Turtle*>(e->obj)) {
				Turtle* turtle = dynamic_cast<Turtle*>(e->obj);

				// jump on top >> kill Goomba and deflect a bit 
				if (e->ny < 0)
				{
					x += min_tx * dx + nx * 0.4f;
					if (x < 10) x = 10;
					if (nx != 0) { vx = 0; }

					y += min_ty * dy + ny * 0.4f;
					if (ny != 0) { vy = 0; }

					turtle->setPatrol(0);

					// alternatives setstate algorithm 
					/*if (turtle->GetState() == TURTLE_STATE_ONFOOT) { 
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						turtle->setState(TURTLE_STATE_TURTLED); 
					}
					else if (turtle->GetState() == TURTLE_STATE_WINGED) {
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						turtle->setState(TURTLE_STATE_ONFOOT);
					}
					else if (turtle->GetState() == TURTLE_STATE_SPINNING) {
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						turtle->setState(TURTLE_STATE_TURTLED);
					}
					else if (turtle->GetState() == TURTLE_STATE_FLIPPED_SPINNING) {
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						turtle->setState(TURTLE_STATE_FLIPPED);
					}*/ 

					switch (turtle->GetState()) {

					case TURTLE_STATE_ONFOOT:
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						turtle->setState(TURTLE_STATE_TURTLED);
						break;

					case TURTLE_STATE_WINGED:
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						turtle->setState(TURTLE_STATE_ONFOOT);
						break;

					case TURTLE_STATE_SPINNING:
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						turtle->setState(TURTLE_STATE_TURTLED);
						break;

					case TURTLE_STATE_FLIPPED_SPINNING:
						vy = -MARIO_JUMP_DEFLECT_SPEED;
						turtle->setState(TURTLE_STATE_FLIPPED);
						break;

					case TURTLE_STATE_FLIPPED:
						turtle->setnx(this->nx);
						turtle->setState(TURTLE_STATE_FLIPPED_SPINNING);

					case TURTLE_STATE_TURTLED:
						turtle->setnx(this->nx);
						turtle->setState(TURTLE_STATE_SPINNING);

					default:
						break;
					}
				}
				else if (e->nx != 0)
				{
					if(turtle->GetState() != TURTLE_STATE_TURTLED && turtle->GetState() != TURTLE_STATE_FLIPPED)
					Reset();
					else {
						turtle->setnx(this->nx);
						if (turtle->GetState() == TURTLE_STATE_TURTLED) turtle->setState(TURTLE_STATE_SPINNING);
						else turtle->setState(TURTLE_STATE_FLIPPED_SPINNING);
						this->State = MARIO_STATE_KICK;
					}
				}
			}
			else if (dynamic_cast<CollidableObstacle*>(e->obj)) {
				CollidableObstacle* CoObs = dynamic_cast<CollidableObstacle*>(e->obj);
				if (CoObs->GetTopOnly() && ( e->ny > 0 || e->nx!=0) ) {
						if (e->ny > 0) {
						y += dy;
						x += min_tx * dx + nx * 0.4f;
						if (x < 10) x = 10;
						if (nx != 0) { vx = 0; }
					}
					if (e->nx != 0) { 
						x += dx; 
						if (x < 10) x = 10; 
						y += min_ty * dy + ny * 0.4f;
						if (ny != 0) { vy = 0; }
					}
				}
				else {
					x += min_tx * dx + nx * 0.4f;
					if (x < 10) x = 10;
					if (nx != 0) { vx = 0; }

					y += min_ty * dy + ny * 0.4f;
					if (ny != 0) { vy = 0; }
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void Mario::Render() {

	int ani=-1;

	if (Level == MARIO_LEVEL_BIG) {
		if (State == MARIO_STATE_KICK) if (nx == 1) ani = MARIO_ANI_BIG_KICK_RIGHT;
		else ani = MARIO_ANI_BIG_KICK_LEFT;
		else if (State == MARIO_STATE_DIVE) if (nx == 1) ani = MARIO_ANI_BIG_DIVE_RIGHT;
		else ani = MARIO_ANI_BIG_DIVE_LEFT;
		else if (vy < 0 || vy> 0.017) if (nx == 1) ani = MARIO_ANI_BIG_JUMP_RIGHT;
		else ani = MARIO_ANI_BIG_JUMP_LEFT;
		else if (vx > 0) if (nx == -1) ani = MARIO_ANI_BIG_BRAKE_RIGHT;
		else if (vx > MARIO_WALKING_SPEED + 0.5f) ani = MARIO_ANI_BIG_SPRINT_RIGHT;
		else ani = MARIO_ANI_BIG_WALK_RIGHT;
		else if (vx < 0) if (nx == 1) ani = MARIO_ANI_BIG_BRAKE_LEFT;
		else if (vx > -MARIO_WALKING_SPEED - 0.5f) ani = MARIO_ANI_BIG_SPRINT_LEFT;
		else ani = MARIO_ANI_BIG_WALK_LEFT;
		else if (nx == 1) ani = MARIO_ANI_BIG_IDLE_RIGHT;
		else ani = MARIO_ANI_BIG_IDLE_LEFT;
	}
	else if (Level == MARIO_LEVEL_SMALL) {
		if (State == MARIO_STATE_KICK) if (nx == 1) ani = MARIO_ANI_SMALL_KICK_RIGHT;
		else ani = MARIO_ANI_SMALL_KICK_LEFT;
		else if (vy < 0 || vy> 0.017) if (nx == 1) ani = MARIO_ANI_SMALL_JUMP_RIGHT;
		else ani = MARIO_ANI_SMALL_JUMP_LEFT;
		else if (vx > 0) if (nx == -1) ani = MARIO_ANI_SMALL_BRAKE_RIGHT;
		else if (vx > MARIO_WALKING_SPEED + 0.5f) ani = MARIO_ANI_SMALL_SPRINT_RIGHT;
		else ani = MARIO_ANI_SMALL_WALK_RIGHT;
		else if (vx < 0) if (nx == 1) ani = MARIO_ANI_SMALL_BRAKE_LEFT;
		else if (vx > -MARIO_WALKING_SPEED - 0.5f) ani = MARIO_ANI_SMALL_SPRINT_LEFT;
		else ani = MARIO_ANI_SMALL_WALK_LEFT;
		else if (nx == 1) ani = MARIO_ANI_SMALL_IDLE_RIGHT;
		else ani = MARIO_ANI_SMALL_IDLE_LEFT;
	}
	else if (Level == MARIO_LEVEL_RACOON) {
		if (State == MARIO_STATE_KICK) if (nx == 1) ani = MARIO_ANI_RACOON_KICK_RIGHT;
		else ani = MARIO_ANI_RACOON_KICK_LEFT;
		else if (State == MARIO_STATE_FLOATTING) if (nx == 1) ani = MARIO_ANI_RACOON_TAIL_FLAPPING_RIGHT;
		else ani = MARIO_ANI_RACOON_TAIL_FLAPPING_LEFT;
		else if (State == MARIO_STATE_DIVE) if (nx == 1) ani = MARIO_ANI_RACOON_DIVE_RIGHT;
		else ani = MARIO_ANI_RACOON_DIVE_LEFT;
		else if (vy < 0 || vy> 0.017) if (nx == 1) ani = MARIO_ANI_RACOON_JUMP_RIGHT;
		else ani = MARIO_ANI_RACOON_JUMP_LEFT;
		else if (vx > 0) if (nx == -1) ani = MARIO_ANI_RACOON_BRAKE_RIGHT;
		else if (vx > MARIO_WALKING_SPEED + 0.5f) ani = MARIO_ANI_RACOON_SPRINT_RIGHT;
		else ani = MARIO_ANI_RACOON_WALK_RIGHT;
		else if (vx < 0) if (nx == 1) ani = MARIO_ANI_RACOON_BRAKE_LEFT;
		else if (vx > -MARIO_WALKING_SPEED - 0.5f) ani = MARIO_ANI_RACOON_SPRINT_LEFT;
		else ani = MARIO_ANI_RACOON_WALK_LEFT;
		else if (nx == 1) ani = MARIO_ANI_RACOON_IDLE_RIGHT;
		else ani = MARIO_ANI_RACOON_IDLE_LEFT;
	}
	Animation_Set->at(ani)->Render(x, y);

	RenderBoundingBox();

}

void Mario::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (this->Level == MARIO_LEVEL_SMALL) {
			left = x;
			top = y;
			right = x + MARIO_SMALL_BBOX_WIDTH;
			bottom = y + MARIO_SMALL_BBOX_HEIGHT;
	}
	else if (this->Level == MARIO_LEVEL_BIG) {
		if (this->State == MARIO_STATE_DIVE) {
			left = x;
			top = y + 9;

			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
		else {
			left = x;
			top = y;

			right = x + MARIO_BIG_BBOX_WIDTH;
			bottom = y + MARIO_BIG_BBOX_HEIGHT;
		}
	}
	else if (this->Level == MARIO_LEVEL_RACOON) {
		if (this->State == MARIO_STATE_DIVE) {
			left = x;
			top = y + 9;

			right = x + MARIO_RACOON_BBOX_WIDTH;
			bottom = y + MARIO_RACOON_BBOX_HEIGHT;
		}
		else if (nx == 1) {

			left = x + 8;
			top = y;

			right = x + MARIO_RACOON_BBOX_WIDTH;
			bottom = y + MARIO_RACOON_BBOX_HEIGHT;
		}
		else if (nx == -1) {

			left = x;
			top = y;

			right = x + MARIO_RACOON_BBOX_WIDTH - 8;
			bottom = y + MARIO_RACOON_BBOX_HEIGHT;
		}
		else {
			left = x;
			top = y;

			right = x + MARIO_RACOON_BBOX_WIDTH;
			bottom = y + MARIO_RACOON_BBOX_HEIGHT;
		}
	}
}

void Mario::setState(int State){

		switch (State)
		{
		case MARIO_STATE_JUMP:

			if (vy >= 0 && vy < 0.017) vy = -MARIO_JUMP_SPEED;
			else if (this->Level == MARIO_LEVEL_RACOON) {
			
			}
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
			if (this->Level != MARIO_LEVEL_SMALL) {
				if (vx > 0) {
					ax = -MARIO_FISSION;
					if (vx < MARIO_FISSION * 1.5 * dt) { vx = 0; ax = 0; }
				}
				if (vx < 0) {
					ax = MARIO_FISSION;
					if (vx > -MARIO_FISSION * 1.5 * dt) { vx = 0; ax = 0; }
				}
			}
			else return;
			break;
		case MARIO_STATE_SPRINT_RIGHT:

			if (vx <= MARIO_SPRINTING_SPEED) ax = MARIO_FISSION;
			else ax = 0;
			nx = 1;
			break;

		case MARIO_STATE_SPRINT_LEFT:

			if (vx >= -MARIO_SPRINTING_SPEED) ax = -MARIO_FISSION;
			else ax = 0;
			nx = -1;
			break;
		default:

			break;
		}

		CGameObject::setState(State);
}

void Mario::setLevel(int level) {

	if (this->Level == MARIO_LEVEL_SMALL && level == MARIO_LEVEL_BIG) {
		this->Level = MARIO_LEVEL_BIG;
		this->y -= 13;
	}
	else if (this->Level == MARIO_LEVEL_BIG && level == MARIO_LEVEL_RACOON) {
		this->Level = MARIO_LEVEL_RACOON;
		this->y -= 1;
	}
}