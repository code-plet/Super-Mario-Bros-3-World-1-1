#pragma once

#include <unordered_map>
#include <d3dx9.h>
#include <Windows.h>

#include "Utils.h"
#include "Sprite.h"

class AnimationFrame //A frame is a sprite in a specific time window 
{

protected:
	LPSPRITE sprite;
    DWORD time;

public:

	AnimationFrame(LPSPRITE sprite, DWORD Time) { this->sprite = sprite; this->time = Time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }

}; typedef AnimationFrame* LPANIMATIONFRAME;

class Animation {

protected:

	DWORD lastFrameTime; 
	int currentFrame;
	int defaultTime;

	vector<LPANIMATIONFRAME> frames;

public:

	Animation(int defaulttime=100) { this->defaultTime = defaulttime; lastFrameTime = -1; currentFrame = -1; }

	void Add(int SpriteID, DWORD time);

	void Render(float x, float y, int alpha = 255);

}; typedef Animation* LPANIMATION;


class Animations {

protected:

	static Animations* Instance;

	unordered_map<int, LPANIMATION> AnimationsSeq;

public:

	void add(int id, LPANIMATION newani);
	LPANIMATION GetAnimation(int id);

	void Clear();

	static Animations* GetInstance();

};

typedef vector<LPANIMATION> AnimationSet;
typedef AnimationSet* LPANIMATIONSET;


class AnimationSets {

protected:

	static AnimationSets* Instance;
	unordered_map<int, LPANIMATIONSET> AniSeqList;

public:

	AnimationSets() {}

	void add(int id, LPANIMATIONSET ani);
	LPANIMATIONSET GetSet(int id);

	static AnimationSets* GetInstance();

};

