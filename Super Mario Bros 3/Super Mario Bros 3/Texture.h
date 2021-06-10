#pragma once

#include <unordered_map>
#include <d3dx9.h>

using namespace std;

class Textures
{
protected:

	static Textures* Instance;
	unordered_map<int, LPDIRECT3DTEXTURE9> textures;

public:

	Textures() {}

	void Add(int id, LPCWSTR FilePath, D3DCOLOR transparentColor);
	LPDIRECT3DTEXTURE9 GetTexture(int id);

	void Clear();

	static Textures* GetInstance();
};

