#include "Turtle.h"
#include "CollidableObstacle.h"
#include "BreakableBrick.h"
#include "QuestionMarkBrick.h"

Turtle::Turtle() {

	this->color = TURTLE_GREEN;
	this->patrol = 0;
	this->setState(TURTLE_STATE_ONFOOT);
	nx = -1;
}

Turtle::Turtle(int startingstate, int color) {
	this->color = color;
	this->patrol = 0;
	this->setState(startingstate);
	nx = -1;
}

Turtle::Turtle(int startingstate, int color, float pointA_x, float pointA_y, float pointB_x, float pointB_y) {
	this->color = color;
	this->patrol = 1;
	this->setState(startingstate);
	nx = -1;
	this->pointA_x = pointA_x;
	this->pointA_y = pointA_y;
	this->pointB_x = pointB_x;
	this->pointB_y = pointB_y;
}

void Turtle::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) {

	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (patrol == true) {

		x += dx;
		y += dy;
		if (abs(this->x - this->pointA_x) <= 5 && abs(this->y - this->pointA_y) <= 5 || abs(this->x - this->pointB_x) <= 5 && abs(this->y - this->pointB_y) <= 5) {
			nx = -nx;
			vy = -vy;
			vx = -vx;
		}

	}
	else {

		ay = TURTLE_GRAVITY;

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
				if (dynamic_cast<QuestionMarkBrick*>(e->obj)) {
					QuestionMarkBrick* CoObs = dynamic_cast<QuestionMarkBrick*>(e->obj);
					y += min_ty * dy + ny * 0.4f;
					if (ny != 0) { vy = 0; }

					x += min_tx * dx + nx * 0.4f;
					if (nx != 0 && !CoObs->GetTopOnly()) {
						this->nx = -nx;
						vx = -vx;
						CoObs->setState(QUESTION_MARK_STATE_DEPLOY);
					}
				}
				else if (dynamic_cast<BreakableBrick*>(e->obj)) {
					BreakableBrick* CoObs = dynamic_cast<BreakableBrick*>(e->obj);
					y += min_ty * dy + ny * 0.4f;
					if (ny != 0) { vy = 0; }

					x += min_tx * dx + nx * 0.4f;
					if (nx != 0 && CoObs->GetTopOnly()==false) {
						this->nx = -nx;
						vx = -vx;
						CoObs->setState(BRICK_STATE_BROKEN);
					}
				}
				else if (dynamic_cast<CollidableObstacle*>(e->obj)) {
					CollidableObstacle* CoObs = dynamic_cast<CollidableObstacle*>(e->obj);
					y += min_ty * dy + ny * 0.4f;
					if (ny != 0) { vy = 0; }

					x += min_tx * dx + nx * 0.4f;
					if (nx != 0 && CoObs->GetTopOnly()==false) {
						this->nx = -nx;
						vx = -vx;
					}
					else {
						x += dx;
					}
					if (x < 10) x = 10;
					if (this->State == TURTLE_STATE_WINGED && vy == 0) vy = TURTLE_JUMP;
				}
			}

			for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
		}
	}
}

void Turtle::Render() {
	int ani = -1;
	if (color == TURTLE_GREEN) {
		if (this->State == TURTLE_STATE_WINGED) {
			if (nx == 1) ani = TURTLE_GREEN_ANI_WINGED_RIGHT;
			else ani = TURTLE_GREEN_ANI_WINGED_LEFT;
		}
		else if (this->State == TURTLE_STATE_ONFOOT) {
			if (nx == 1) ani = TURTLE_GREEN_ANI_ONFOOT_RIGHT;
			else ani = TURTLE_GREEN_ANI_ONFOOT_LEFT;
		}
		else if (this->State == TURTLE_STATE_TURTLED)
			ani = TURTLE_GREEN_ANI_TURTLED;
		else if (this->State == TURTLE_STATE_FLIPPED)
			ani = TURTLE_GREEN_ANI_FLIPPED;
		else if (this->State == TURTLE_STATE_SPINNING) {
			if (nx == 1) ani = TURTLE_GREEN_ANI_SPINNING_RIGHT;
			else ani = TURTLE_GREEN_ANI_SPINNING_LEFT;
		}
		else if (this->State == TURTLE_STATE_FLIPPED_SPINNING) {
			if (nx == 1) ani = TURTLE_GREEN_ANI_FLIPPED_SPINNING_RIGHT;
			else ani = TURTLE_GREEN_ANI_FLIPPED_SPINNING_LEFT;
		}
	} 
	else if (color == TURTLE_RED) {
		if (this->State == TURTLE_STATE_WINGED) {
			if (nx == 1) ani = TURTLE_RED_ANI_WINGED_RIGHT;
			else ani = TURTLE_RED_ANI_WINGED_LEFT;
		}
		else if (this->State == TURTLE_STATE_ONFOOT) {
			if (nx == 1) ani = TURTLE_RED_ANI_ONFOOT_RIGHT;
			else ani = TURTLE_RED_ANI_ONFOOT_LEFT;
		}
		else if (this->State == TURTLE_STATE_TURTLED)
			ani = TURTLE_RED_ANI_TURTLED;
		else if (this->State == TURTLE_STATE_FLIPPED)
			ani = TURTLE_RED_ANI_FLIPPED;
		else if (this->State == TURTLE_STATE_SPINNING) {
			if (nx == 1) ani = TURTLE_RED_ANI_SPINNING_RIGHT;
			else ani = TURTLE_RED_ANI_SPINNING_LEFT;
		}
		else if (this->State == TURTLE_STATE_FLIPPED_SPINNING) {
			if (nx == 1) ani = TURTLE_RED_ANI_FLIPPED_SPINNING_RIGHT;
			else ani = TURTLE_RED_ANI_FLIPPED_SPINNING_LEFT;
		}
	}
	Animation_Set->at(ani)->Render(x, y);
}

void Turtle::setState(int State) {

	this->State = State;
	switch (State)
	{
	case TURTLE_STATE_TURTLED:
		vx = 0;
		vy = 0;
		break;
	case TURTLE_STATE_WINGED:
		if(nx==1) vx = TURTLE_WALKING_SPEED;
		else vx = -TURTLE_WALKING_SPEED;
		break;
	case TURTLE_STATE_ONFOOT:
		if (nx == 1) vx = TURTLE_WALKING_SPEED;
		else vx = -TURTLE_WALKING_SPEED;
		break;
	case TURTLE_STATE_SPINNING:
		if (nx == 1) vx = TURTLE_SPINNING_SPEED;
		else vx = -TURTLE_SPINNING_SPEED;
		break;
	default:
		break;
	}
}

void Turtle::GetBoundingBox(float& left, float& top, float& right, float& bottom) {

	if (this->State == TURTLE_STATE_WINGED) {
		left = x;
		top = y;
		right = x + TURTLE_WINGED_WIDTH;
		bottom = y + TURTLE_WINGED_HEIGHT;
	}
	else if (this->State == TURTLE_STATE_ONFOOT) {
		left = x;
		top = y;
		right = x + TURTLE_ONFOOT_WIDTH;
		bottom = y + TURTLE_ONFOOT_HEIGHT;
	}
	else {
		left = x;
		top = y;
		right = x + TURTLE_TURTLED_WIDTH;
		bottom = y + TURTLE_TURTLED_HEIGHT;
	}

}