#include <math.h>

#include "VenusFireTrap.h"
#include "PlayScene.h"
#include "Fireball.h"

VenusFireTrap::VenusFireTrap(int color) {

	this->color = color;
	setState(VENUSFIRETRAP_STATE_SLEEP);

}

void VenusFireTrap::Update(DWORD dt, vector <LPGAMEOBJECT>* coObjects) { // Separate Firetrap into consecutive stages for easy coding  

	CGameObject::Update(dt);
	y += dy;
	float mario_x, mario_y;
	Mario* mario = Cgame::GetInstance()->GetCurrentScene()->GetPlayer();
	mario->GetLocation(mario_x, mario_y);
	if (this->State == VENUSFIRETRAP_STATE_SLEEP) {
		if (abs(this->x - mario_x) < 200 && abs(this->y - mario_y) < 100) 
			if(mario_x-this->x<=25 && mario_x - this->x >=-10 && this->y - mario_y <= 45 && this->y - mario_y >= -2) {
				setState(VENUSFIRETRAP_STATE_HIDE);
			}
			else {
				this->OG_y = this->y;
				setState(VENUSFIRETRAP_STATE_DEPLOY);
			}
	}
	else if (OG_y - y > VENUSFIRETRAP_HEIGHT+6 && this->State==VENUSFIRETRAP_STATE_DEPLOY) {
		this->setState(VENUSFIRETRAP_STATE_FIRE);
		this->Ready_time = GetTickCount();
	}
	else if (this->State == VENUSFIRETRAP_STATE_FIRE) {

		DWORD currenttime = GetTickCount();
		if (currenttime - this->Ready_time > VENUSFIRETRAP_WAIT_TIME) // wait for <time> then fire then wait again before going down
		{
			CGameObject::GetObjectPosition(this->x, this->y, mario_x, mario_y);
			LPGAMEOBJECT fireball = new Fireball(CGameObject::GetObjectPosition(this->x, this->y, mario_x, mario_y));
			Cgame::GetInstance()->GetCurrentScene()->AddGameObject(fireball, this->x + 5, this->y + 5, FIREBALL_ANIMATION_SET);

			this->Ready_time = GetTickCount();
			this->setState(VENUSFIRETRAP_STATE_FIRED);
		}
	}
	else if (this->State == VENUSFIRETRAP_STATE_FIRED) {
		DWORD currenttime = GetTickCount();
		if (currenttime - this->Ready_time > VENUSFIRETRAP_WAIT_TIME)
		{
			this->Ready_time = GetTickCount();
			this->setState(VENUSFIRETRAP_STATE_HIDE);
		}
	}
	else if (this->State == VENUSFIRETRAP_STATE_HIDE) {
		if (this->y >= this->OG_y) {
			this->y = OG_y;
			vy = 0;
			DWORD currenttime = GetTickCount();
			if (currenttime - this->Ready_time > VENUSFIRETRAP_WAIT_TIME*2.5)
			{
				this->setState(VENUSFIRETRAP_STATE_SLEEP);
			}
		}
	}
}

void VenusFireTrap::Render()
{
	int ani = -1;
	float mario_x, mario_y;
	Cgame::GetInstance()->GetCurrentScene()->GetPlayer()->GetLocation(mario_x, mario_y);
	if (this->color == 0) {
		if (this->State == VENUSFIRETRAP_STATE_SLEEP || this->State == VENUSFIRETRAP_STATE_FIRE || this->State == VENUSFIRETRAP_STATE_FIRED) {

			if (mario_x > this->x) {
				if (mario_y > this->y) ani = VENUSFIRETRAP_ANI_RED_FIRE_DOWN_RIGHT;
				else ani = VENUSFIRETRAP_ANI_RED_FIRE_UP_RIGHT;
			}
			else {
				if (mario_y > this->y) ani = VENUSFIRETRAP_ANI_RED_FIRE_DOWN_LEFT;
				else ani = VENUSFIRETRAP_ANI_RED_FIRE_UP_LEFT;
			}
		}
		else if (this->State == VENUSFIRETRAP_STATE_DEPLOY || this->State == VENUSFIRETRAP_STATE_HIDE) {
			if (mario_x > this->x) {
				if (mario_y > this->y) ani = VENUSFIRETRAP_ANI_RED_DEPLOYING_DOWN_RIGHT;
				else ani = VENUSFIRETRAP_ANI_RED_DEPLOYING_UP_RIGHT;
			}
			else {
				if (mario_y > this->y) ani = VENUSFIRETRAP_ANI_RED_DEPLOYING_DOWN_LEFT;
				else ani = VENUSFIRETRAP_ANI_RED_DEPLOYING_UP_LEFT;
			}
		}
	}
	else {
		if (this->State == VENUSFIRETRAP_STATE_SLEEP || this->State == VENUSFIRETRAP_STATE_FIRE || this->State == VENUSFIRETRAP_STATE_FIRED) {

			if (mario_x > this->x) {
				if (mario_y > this->y) ani = VENUSFIRETRAP_ANI_GREEN_FIRE_DOWN_RIGHT;
				else ani = VENUSFIRETRAP_ANI_GREEN_FIRE_UP_RIGHT;
			}
			else {
				if (mario_y > this->y) ani = VENUSFIRETRAP_ANI_GREEN_FIRE_DOWN_LEFT;
				else ani = VENUSFIRETRAP_ANI_GREEN_FIRE_UP_LEFT;
			}
		}
		else if (this->State == VENUSFIRETRAP_STATE_DEPLOY || this->State == VENUSFIRETRAP_STATE_HIDE) {
			if (mario_x > this->x) {
				if (mario_y > this->y) ani = VENUSFIRETRAP_ANI_GREEN_DEPLOYING_DOWN_RIGHT;
				else ani = VENUSFIRETRAP_ANI_GREEN_DEPLOYING_UP_RIGHT;
			}
			else {
				if (mario_y > this->y) ani = VENUSFIRETRAP_ANI_GREEN_DEPLOYING_DOWN_LEFT;
				else ani = VENUSFIRETRAP_ANI_GREEN_DEPLOYING_UP_LEFT;
			}
		}
	}
	

	Animation_Set->at(ani)->Render(x, y);
}

void VenusFireTrap::setState(int State) {
	this->State = State;
	switch (State)
	{
	case VENUSFIRETRAP_STATE_DEPLOY:
		this->vy = -VENUSFIRETRAP_SPEED;
		break;
	case VENUSFIRETRAP_STATE_FIRE:
		this->vy = 0;
		break;
	case VENUSFIRETRAP_STATE_HIDE:
		this->vy = VENUSFIRETRAP_SPEED;
		break;
	default:
		break;
	}
}

void VenusFireTrap::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = this->x;
	top = this->y;
	right = x + VENUSFIRETRAP_WIDTH;
	bottom = y + VENUSFIRETRAP_HEIGHT;
}
