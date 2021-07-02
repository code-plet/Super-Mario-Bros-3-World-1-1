#pragma once

#include <string>
#include <vector>
#include "Mario.h"
#include "Scene.h"


class PlayScene : public Scene 
{
protected:

	Mario* Player;  //Main object of a scene

	vector<LPGAMEOBJECT> GameObject; //All objects in the scene

	void ParseSectionTexture(string line);
	void ParseSectionSprites(string line);
	void ParseSectionAnimations(string line);
	void ParseSectionAnimationSets(string line);
	void ParseSectionObjects(string line);

public:

	PlayScene(int id, LPCWSTR FilePath);

	Mario* GetPlayer() { return Player; }

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Unload();
	virtual void Render();

	void clear();

}; typedef PlayScene* LPPLAYSCENE;

class PlaySceneKeyHandler : public SceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) {};
	PlaySceneKeyHandler(LPSCENE s) :SceneKeyHandler(s) {};
};

