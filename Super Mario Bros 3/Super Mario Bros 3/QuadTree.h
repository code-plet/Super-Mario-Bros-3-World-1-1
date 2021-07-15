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
	bool Divided = false; 
	QuadTree* topright = NULL;
	QuadTree* topleft = NULL;
	QuadTree* bottomright = NULL;
	QuadTree* bottomleft = NULL;
	
public:

	QuadTree(rect boundary, int capacity);
	QuadTree(float left, float top, float right, float bottom, int capacity);

	bool Insert(LPGAMEOBJECT obj);
	void Divide();

	void DeleteDeadObjects(rect camera);

	void Query(rect camera, vector<LPGAMEOBJECT>* CoObjects = NULL);
	bool Intersect(rect camera);
	bool Intersect(rect camera, rect object);

	void Delete();

};

