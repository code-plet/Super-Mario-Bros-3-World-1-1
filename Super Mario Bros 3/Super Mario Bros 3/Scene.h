#pragma once

#include "KeyEventHandler.h"

class Mario;

class Scene
{
protected:

	CKeyEventHandler* KeyHandler;
	int id;
	LPCWSTR SceneFilePath;

public: 

	Scene(int id, LPCWSTR filepath);

	CKeyEventHandler* GetKeyHandler() { return KeyHandler; }

	virtual Mario* GetPlayer() = 0;
	virtual void Load() = 0;
	virtual void Unload() = 0;
	virtual void Update(DWORD dt) = 0;
	virtual void Render() = 0;
}; typedef Scene* LPSCENE;

class SceneKeyHandler : public CKeyEventHandler 
{
protected:

	LPSCENE Scene;

public:

	virtual void KeyState(BYTE* states) =0;
	virtual void OnKeyDown(int KeyCode) =0;
	virtual void OnKeyUp(int KeyCode) =0;
	SceneKeyHandler(LPSCENE s) :CKeyEventHandler() { Scene = s; }
};

