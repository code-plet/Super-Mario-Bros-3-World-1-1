#include "QuadTree.h"

QuadTree::QuadTree(rect boundary, int capacity) {
	this->boundary = boundary;
	this->capacity = capacity;
}

QuadTree::QuadTree(float left, float top, float right, float bottom, int capacity) {
	boundary.left = left;
	boundary.top = top;
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
			if (this->Divided) {
				if (this->bottomleft->Insert(obj));
				else if (this->bottomright->Insert(obj));
				else if (this->topleft->Insert(obj));
				else this->topright->Insert(obj);
			}
			else {
				this->Object_List.push_back(obj);
				this->Divide();
			}
		}
		return true;
	}
	else return false;
}

void QuadTree::Divide() {

	this->topleft = new QuadTree(boundary.left, boundary.top, boundary.right - ((boundary.right- boundary.left)/2) , boundary.bottom - ((boundary.bottom- boundary.top)/2), this->capacity );
	for (int i = 0; i < this->Object_List.size(); i++) {
		topleft->Insert(this->Object_List[i]);
	}

	this->topright = new QuadTree(boundary.left + ((boundary.right - boundary.left) / 2), boundary.top, boundary.right, boundary.bottom - ((boundary.bottom - boundary.top) / 2), this->capacity);
	for (int i = 0; i < this->Object_List.size(); i++) {
		topright->Insert(this->Object_List[i]);
	}

	this->bottomleft = new QuadTree(boundary.left, boundary.top + ((boundary.bottom - boundary.top) / 2), boundary.right - ((boundary.right - boundary.left)/2), boundary.bottom, this->capacity);
	for (int i = 0; i < this->Object_List.size(); i++) {
		bottomleft->Insert(this->Object_List[i]);
	}

	this->bottomright = new QuadTree(boundary.left + ((boundary.right - boundary.left) / 2), boundary.top + ((boundary.bottom - boundary.top) / 2), boundary.right, boundary.bottom, this->capacity);
	for (int i = 0; i < this->Object_List.size(); i++) {
		bottomright->Insert(this->Object_List[i]);
	}
	this->Divided = true;
}

void QuadTree::Query(rect camera, vector<LPGAMEOBJECT>* RenderObjects) {
	if (!this->Intersect(camera)) {
		return;
	}
	else {
		if (this->Divided) {
			this->bottomleft->Query(camera, RenderObjects);
			this->bottomright->Query(camera, RenderObjects);
			this->topleft->Query(camera, RenderObjects);
			this->topright->Query(camera, RenderObjects);
		}
		else {
			for (int i = 0; i < this->Object_List.size(); i++) {
				rect obj;
				float obj_x, obj_y;
				Object_List[i]->GetBoundingBox(obj.left, obj.top, obj.right, obj.bottom);
				Object_List[i]->GetLocation(obj_x, obj_y);
				if (Intersect(camera, obj) ||
					obj_x >= camera.left && obj_x <= camera.right && obj_y >= camera.top && obj_y <= camera.bottom ||
					obj.right - obj.left >= 150) {
					RenderObjects->push_back(Object_List[i]);
				}
			}
		}
	}
}

void QuadTree::DeleteDeadObjects(rect camera) {
	if (!this->Intersect(camera)) {
		return;
	}
	else {
		if (this->Divided) {
			this->bottomleft->DeleteDeadObjects(camera);
			this->bottomright->DeleteDeadObjects(camera);
			this->topleft->DeleteDeadObjects(camera);
			this->topright->DeleteDeadObjects(camera);
		}
		else {
			for (int i = 0; i < this->Object_List.size(); i++) {
				if (Object_List[i]->GetState() == 66) {
					Object_List.erase(Object_List.begin() + i);
				}
				
			}
		}
	}
}

bool QuadTree::Intersect(rect camera) {
	if (this->boundary.left == this->boundary.right || this->boundary.top == this->boundary.bottom || camera.left == camera.right
		|| camera.top == camera.bottom) {
		return false;
	}

	if (this->boundary.left >= camera.right || camera.left >= this->boundary.right)
		return false;

	if (this->boundary.top >= camera.bottom || camera.top >= this->boundary.bottom)
		return false;

	return true;
}

bool QuadTree::Intersect(rect camera, rect object) {
	if (object.left == object.right || object.top == object.bottom || camera.left == camera.right
		|| camera.top == camera.bottom) {
		return false;
	}

	if (object.left >= camera.right || camera.left >= object.right)
		if (object.left == 624 && object.right == 384) DebugOut(L"cameraleft: %f; cameraright: %f; objleft: %f; objright: %f\n", camera.left,camera.right,object.left,object.right);
		return false;

	if (object.top >= camera.bottom || camera.top >= object.bottom)
		if (object.left == 624 && object.right == 384) DebugOut(L"cameratop: %f; camerabottom: %f; objtop: %f; objbottom: %f\n", camera.top, camera.bottom, object.top, object.bottom);
		return false;

	return true;
}

void QuadTree::Delete() { 
	if (this->Divided == true) {
		this->bottomleft->Delete();
		this->bottomright->Delete();
		this->topright->Delete();
		this->topleft->Delete();
	}
	else {
		for (int i = 0; i < this->Object_List.size(); i++) {
			delete Object_List[i];
		}
		this->Object_List.clear();
		delete this;
		return;
	}
}



