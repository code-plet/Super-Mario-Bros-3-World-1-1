#include "Sprite.h"
#include "Utils.h"

Sprite::Sprite(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex) {
	this->id = id;
	this->left = left;
	this->top = top;
	this->right = right;
	this->bottom = bottom;
	this->texture = tex;
}

void Sprite::Draw(float x, float y, int alpha) {

	Cgame* game = Cgame::GetInstance();
	game->Draw(x, y, texture, left, top, right, bottom, alpha);
	
}

Sprites* Sprites::Instance = NULL;

Sprites* Sprites::GetInstance() {
	if (Instance == NULL) Instance = new Sprites();
	return Instance;
}

void Sprites::add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex) {

	LPSPRITE newSprite = new Sprite(id, left, top, right, bottom, tex);
	sprites[id] = newSprite;

	DebugOut(L"[INFO] sprite added: %d, %d, %d, %d, %d \n", id, left, top, right, bottom);
}

void Sprites::Clear() {

	for (auto x : sprites) {

		LPSPRITE sprite = x.second;
		delete sprite;
	}
	sprites.clear();
}

LPSPRITE Sprites::Get(int id) {
	return sprites[id];
}

