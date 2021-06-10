#include <Windows.h>

#include <d3d9.h>
#include <d3dx9.h>

#include "Texture.h"
#include "Utils.h"
#include "Cgame.h"

Textures* Textures::Instance = NULL;

void Textures::Add(int id, LPCWSTR FilePath, D3DCOLOR transparentColor) {

	D3DXIMAGE_INFO info;
	HRESULT result = D3DXGetImageInfoFromFile(FilePath, &info);
	if (result != D3D_OK) {
		
		DebugOut(L"[ERROR] GetImageInfoFromFile failed: %s\n", FilePath);
		return;
	}

	LPDIRECT3DDEVICE9 d3ddv = Cgame::GetInstance()->GetDirect3DDevice();
	LPDIRECT3DTEXTURE9 texture;

	result = D3DXCreateTextureFromFileEx(

		d3ddv,								// Pointer to Direct3D device object
		FilePath,							// Path to the image to load
		info.Width,							// Texture width
		info.Height,						// Texture height
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		transparentColor,
		& info,
		NULL,
		& texture);								// Created texture pointer

	if (result != D3D_OK)
	{
		OutputDebugString(L"[ERROR] CreateTextureFromFile failed\n");
		return;
	}

	textures[id] = texture;

	DebugOut(L"[INFO] Texture loaded Ok: id=%d, %s\n", id, FilePath);
}

LPDIRECT3DTEXTURE9 Textures::GetTexture(int id) { return textures[id]; }

void Textures::Clear() {

	for (auto x : textures) {

		LPDIRECT3DTEXTURE9 tex = x.second;
		delete tex;
	}
	textures.clear();

}

Textures* Textures::GetInstance() {

	if (Instance == NULL) Instance = new Textures();
	return Instance;
	
}
