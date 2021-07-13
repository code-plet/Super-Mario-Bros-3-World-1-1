#include "QuadTree.h"

QuadTree::QuadTree(rect boundary, int capacity) {
	this->boundary = boundary;
	this->capacity = capacity;
}

QuadTree::QuadTree(float left, float top, float right, float bottom, int capacity) {
	boundary.top = top;
	boundary.left = left;
	boundary.right = right;
	boundary.bottom = bottom;
	this->capacity = capacity;
}

bool QuadTree::Insert(LPGAMEOBJECT obj) {

	float obj_x, obj_y;
	obj->GetLocation(obj_x, obj_y);
	if ( (obj_x >= this->boundary.left && obj_x <= this->boundary.right)
		 &&
		 (obj_y >= this->boundary.top && obj_y <= this->boundary.bottom)
	)	{
		if (this->Object_List.size() < this->capacity) {
			this->Object_List.push_back(obj);
		}
		else {
			this->Divide(obj);
		}
		return true;
	}
	else return false;
}

void QuadTree::Divide(LPGAMEOBJECT obj) {

	QuadTree* topleft = new QuadTree(boundary.top, boundary.left, boundary.right - ((boundary.right- boundary.left)/2) , boundary.bottom - ((boundary.bottom- boundary.top)/2), this->capacity );
	for (int i = 0; i < this->Object_List.size(); i++) {
		if (topleft->Insert(this->Object_List[i])) this->Object_List.erase(Object_List.begin() + i);
	}

	QuadTree* topright = new QuadTree(boundary.top, boundary.left + ((boundary.right - boundary.left) / 2), boundary.right, boundary.bottom - ((boundary.bottom - boundary.top) / 2), this->capacity);
	for (int i = 0; i < this->Object_List.size(); i++) {
		if (topright->Insert(this->Object_List[i])) this->Object_List.erase(Object_List.begin() + i);
	}

	QuadTree* bottomleft = new QuadTree(boundary.top + ((boundary.bottom- boundary.top)/2), boundary.left, boundary.right - ((boundary.right - boundary.left)/2), boundary.bottom, this->capacity);
	for (int i = 0; i < this->Object_List.size(); i++) {
		if (bottomleft->Insert(this->Object_List[i])) this->Object_List.erase(Object_List.begin() + i);
	}

	QuadTree* bottomright = new QuadTree(boundary.top + ((boundary.bottom - boundary.top)/2), boundary.left + ((boundary.right - boundary.left) / 2), boundary.right, boundary.bottom, this->capacity);
	for (int i = 0; i < this->Object_List.size(); i++) {
		if (bottomright->Insert(this->Object_List[i])) this->Object_List.erase(Object_List.begin() + i);
	}
	this->Divided = true;
}

void Intersect(rect camera, vector<LPGAMEOBJECT>* CoObjects) {
	
}

