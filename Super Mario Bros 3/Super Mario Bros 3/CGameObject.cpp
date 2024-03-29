#include <algorithm>

#include "CGameObject.h"
#include "Texture.h"

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT> *coObjects) {

	this->dt = dt;
	vx += ax * dt;
	vy += ay * dt;
	dx = vx * dt;
	dy = vy * dt;
}

LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;		// static object bbox
	float ml, mt, mr, mb;		// moving object bbox
	float t, nx, ny;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy;
	coO->GetVelocity(svx, svy);

	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx;
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb);

	Cgame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CollisionEvent* e = new CollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/
void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects,
	vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0; i < coObjects->size(); i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
	}

	std::sort(coEvents.begin(), coEvents.end(), CollisionEvent::compare);
}

void CGameObject::FilterCollision(
	vector<LPCOLLISIONEVENT>& coEvents,
	vector<LPCOLLISIONEVENT>& coEventsResult,
	float& min_tx, float& min_ty,
	float& nx, float& ny, float& rdx, float& rdy)
{
	min_tx = 1.0f;
	min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];

		if (c->t < min_tx && c->nx != 0) {
			min_tx = c->t; nx = c->nx; min_ix = i; rdx = c->dx;
		}

		if (c->t < min_ty && c->ny != 0) {
			min_ty = c->t; ny = c->ny; min_iy = i; rdy = c->dy;
		}
	}

	if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);
	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);
}

void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = Textures::GetInstance()->GetTexture(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	Cgame::GetInstance()->Draw(x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}

int CGameObject::GetObjectPosition(float primary_x, float primary_y, float secondary_x, float secondary_y) {

	int direction=-1;
	
	secondary_x -= primary_x;
	secondary_y -= primary_y;

	if (secondary_x > 0) {
		if (secondary_y > 0) {

			//NorthEast
			if (abs(secondary_x) > abs(secondary_y)) {

				direction = DIRECTION_NORTHEAST_LOWER;
			}
			else direction = DIRECTION_NORTHEAST_UPPER;
		}
		else {

			//SouthEast
			if (abs(secondary_x) > abs(secondary_y)) {
				direction = DIRECTION_SOUTHEAST_UPPER;
			}
			else direction = DIRECTION_SOUTHEAST_LOWER;
		}
	}
	else {
		if (secondary_y > 0) {
			//NorthWest
			if (abs(secondary_x) > abs(secondary_y)) {

				direction = DIRECTION_NORTHWEST_LOWER;
			}
			else direction = DIRECTION_NORTHWEST_UPPER;
		}
		else {
			//SouthWest
			if (abs(secondary_x) > abs(secondary_y)) {
				direction = DIRECTION_SOUTHWEST_UPPER;
			}
			else direction = DIRECTION_SOUTHWEST_LOWER;
		}
	}
	return direction;
}