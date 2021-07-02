#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <d3d9.h>
#include <unordered_map>

#define DIRECTINPUT_VERSION 0x0800

#include <dinput.h>

#include "Scene.h"

using namespace std;

#define KEYBOARD_BUFFER_SIZE 1024


class Cgame {

	static Cgame* __instance;  //Unique and only Cgame object 
	HWND          hWnd;      //Main window 

	LPDIRECT3D9 d3d = NULL;             //Direct3D Handler
	LPDIRECT3DDEVICE9 d3ddv = NULL;     //Direct3D Device object

	LPDIRECT3DSURFACE9 backBuffer = NULL;
	LPD3DXSPRITE       spriteHandler = NULL;    // Sprite helper Lib for drawing 2D images on screen

	LPDIRECTINPUT8       di;    //DirectInput object 
	LPDIRECTINPUTDEVICE8 didv;  //Keyboard for DirectInput

	BYTE               keystate[256];  //DirectInput device state-buffer
	DIDEVICEOBJECTDATA KeyEvents[KEYBOARD_BUFFER_SIZE];    //buffered data from keyboard

	LPKEYEVENTHANDLER KeyHandler;

	float cam_x = 0.0f;
	float cam_y = 0.0f;


	unordered_map<int, LPSCENE> scenes;

	int screen_height;
	int screen_width;

	int CurrentScene;

public:

	void InitKeyboard(); 
	void SetKeyHandler(LPKEYEVENTHANDLER handler) { KeyHandler = handler; }
	void Init(HWND HWnd); //Initialize game components
	void Draw(float x, float y, LPDIRECT3DTEXTURE9 texture, int left, int top, int right, int bottom, int alpha = 255); //Draw image from tex. 

	int IsKeyDown(int Keycode);
	void ProcessKeyboard();

	void Load(LPCWSTR gamefile);
	LPSCENE GetCurrentScene();

	int GetScreenHeight() { return this->screen_height; }
	int GetScreenWidth() { return this->screen_width; }

	static void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float& t, float& nx, float& ny);

	void ParseSectionSettings(string line);
	void ParseSectionScenes(string line);

	void SwitchScene(int currentScene);

	LPDIRECT3DDEVICE9 GetDirect3DDevice() { return this->d3ddv; }
	LPDIRECT3DSURFACE9 GetBackBuffer() { return backBuffer; }
	LPD3DXSPRITE GetSpriteHandler() { return this->spriteHandler; }

	void SetcamPos(float x, float y) { cam_x = x; cam_y = y; }

	static Cgame* GetInstance(); //Call the game object's pointer, if NULL create new game.

	~Cgame();

};

