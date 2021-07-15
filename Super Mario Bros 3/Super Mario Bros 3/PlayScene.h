#pragma once

#include <string>
#include <vector>
#include "Mario.h"
#include "Scene.h"
#include "QuadTree.h"


class PlayScene : public Scene 
{
protected:

	Mario* Player;  //Main object of a scene

	QuadTree* quadtree = NULL; //All objects in the scene

	void ParseSectionTexture(string line);
	void ParseSectionSprites(string line);
	void ParseSectionAnimations(string line);
	void ParseSectionAnimationSets(string line);
	void ParseSectionObjects(string line);

public:

	PlayScene(int id, LPCWSTR FilePath);

	Mario* GetPlayer() { return Player; }

	void AddGameObject(LPGAMEOBJECT obj, float x, float y, int Animation_set);

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

