#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Animation.h"
#include "Cgame.h"

using namespace std;

#define ID_TEX_BBOX -100

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CollisionEvent;
typedef CollisionEvent* LPCOLLISIONEVENT;
struct CollisionEvent {

	LPGAMEOBJECT obj;
	float t, nx, ny;

	float dx, dy;

	CollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(const LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b)
	{
		return a->t < b->t;
	}

};

class CGameObject {

protected:

	float x, y;      //Object's current location

	float vx, vy;    //Object's immediate velocity 

	float ax, ay;    //Object's acceleration rate (per frame/dt)

	int nx;         //Object's current direction

	int State;       //Object's state of actions

	LPANIMATIONSET Animation_Set;

	DWORD dt;

public:

	CGameObject(){}

	void setLocation(float x, float y) { this->x = x; this->y = y; }
	void setVelocity(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void setAccel(float ax, float ay) { this->ax = ax; this->ay = ay; }

	int GetState() { return State; }
    float GetVelocity_x() { return this->vx; }
	void GetVelocity(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void GetAccel(float& ax, float& ay) { ax = this->ax; vy = this->ay; }

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom) = 0;
	virtual void Update(DWORD dt,vector <LPGAMEOBJECT> *coObjects = NULL);
	virtual void Render()=0;

	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT obj);
	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEventResult);
	void FilterCollision( vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coEventsResult,
		float& min_tx,
		float& min_ty,
		float& nx,
		float& ny,
		float& rdx,
		float& rdy);

	void RenderBoundingBox();

	void setAnimationSet(LPANIMATIONSET aniset) { Animation_Set = aniset; }
	virtual void setState(int State) { this->State = State; }



}; 
