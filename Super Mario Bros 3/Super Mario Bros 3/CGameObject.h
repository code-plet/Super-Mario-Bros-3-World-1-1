#pragma once

#include <d3d9.h>
#include <d3dx9.h>

#include "Animation.h"
#include "Cgame.h"

using namespace std;

#define ID_TEX_BBOX -100

#define DIRECTION_NORTHWEST_UPPER 0
#define DIRECTION_NORTHWEST_LOWER 1
#define DIRECTION_SOUTHWEST_UPPER 2
#define DIRECTION_SOUTHWEST_LOWER 3
#define DIRECTION_SOUTHEAST_UPPER 4
#define DIRECTION_SOUTHEAST_LOWER 5
#define DIRECTION_NORTHEAST_UPPER 6
#define DIRECTION_NORTHEAST_LOWER 7

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

	float dx, dy;    //Object's immediate velocity

	float vx, vy;    //Object's current velocity 

	float ax, ay;    //Object's acceleration rate 

	int nx;         //Object's current direction

	int State;       //Object's state of actions

	int Width, Height; //easier to get bounding box 

	LPANIMATIONSET Animation_Set;

	DWORD dt;

public:

	CGameObject(){}

	void setLocation(float x, float y) { this->x = x; this->y = y; }
	void setVelocity(float vx, float vy) { this->vx = vx; this->vy = vy; }
	void setAccel(float ax, float ay) { this->ax = ax; this->ay = ay; }
	void setnx(int nx) { this->nx = nx; }

	int GetState() { return State; }
	void GetLocation(float& x, float& y) { x = this->x; y = this->y; }
    float GetVelocity_x() { return this->vx; }
	void GetVelocity(float& vx, float& vy) { vx = this->vx; vy = this->vy; }
	void GetAccel(float& ax, float& ay) { ax = this->ax; vy = this->ay; }

	virtual void SetBoundingBox(int height, int width) { this->Width = width; this->Height = height; }
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

	int GetObjectPosition(float primary_x, float primary_y, float secondary_x, float secondary_y); // calculate secondary object respective position to primary object.

}; 
