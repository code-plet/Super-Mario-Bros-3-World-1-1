#pragma once

#include <vector>

#include "CGameObject.h"

using namespace std;

struct rect { // A rectangle represents camera or quadtree. 
	float left;
	float top;
	float right;
	float bottom;
};

class QuadTree
{
protected:

	rect boundary;	// Represents quadtree rectangle boundary
	int capacity;	// Quadtree object limit 
	vector<LPGAMEOBJECT> Object_List;
	bool Divided; 
	
public:

	QuadTree(rect boundary, int capacity);
	QuadTree(float left, float top, float right, float bottom, int capacity);

	bool Insert(LPGAMEOBJECT obj);
	void Divide(LPGAMEOBJECT obj);
	void Intersect(rect camera, vector<LPGAMEOBJECT> *CoObjects= NULL);

};

