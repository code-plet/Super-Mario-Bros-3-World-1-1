#pragma once

#include <unordered_map>
#include <d3dx9.h>
#include <Windows.h>

#include "Cgame.h"

using namespace std;

class Sprite
{
protected:

	int id;    //Sprite's ID in sprites' Database

	int left, top;       //Upper cutting corner
	int right, bottom;   //Lower cutting corner

	LPDIRECT3DTEXTURE9 texture;

public:

	Sprite(int id, int left, int top , int tight , int bottom, LPDIRECT3DTEXTURE9 tex);

	void Draw(float x, float y, int alpha=255);

};

typedef Sprite* LPSPRITE;

class Sprites
{
protected:

	static Sprites* Instance;
	unordered_map<int, LPSPRITE> sprites;

public:

	void add(int id, int left, int top, int right, int bottom, LPDIRECT3DTEXTURE9 tex);
	LPSPRITE Get(int ID);

	void Clear();

	static Sprites* GetInstance();

};



