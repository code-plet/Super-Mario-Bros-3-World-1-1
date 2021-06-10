#include "Animation.h"


Animations* Animations::Instance = NULL;
AnimationSets* AnimationSets::Instance = NULL;

void Animation::Add(int SpriteID, DWORD time) {

	int t = time;
	if (time == 0) t = this->defaultTime;

	LPSPRITE newsprite = Sprites::GetInstance()->Get(SpriteID);

	if (newsprite == NULL) DebugOut(L"[ERROR] Sprite ID %d cannot be found!\n", SpriteID);

	LPANIMATIONFRAME newFrame = new AnimationFrame (newsprite, time);


	frames.push_back(newFrame);
}

void Animation::Render(float x, float y,int alpha) {

	DWORD now = GetTickCount();
	if (currentFrame == -1) {
		currentFrame = 0;
		lastFrameTime = now;
	}
	else {
		DWORD t = frames[currentFrame]->GetTime();
		if (now - lastFrameTime >= t) {
			currentFrame++;
			lastFrameTime = now;
			if (currentFrame == frames.size()) currentFrame = 0;
		}
	}
	frames[currentFrame]->GetSprite()->Draw(x, y, alpha);
}

void Animations::add(int id, LPANIMATION newani ) { 

	AnimationsSeq[id] = newani; 

}

void Animations::Clear() {

	for (auto x : AnimationsSeq) {

		LPANIMATION ani = x.second;
		delete ani;
	}

	this->AnimationsSeq.clear();
}

Animations* Animations::GetInstance() {

	if (Instance == NULL)  Instance = new Animations();
	return Instance;
}

LPANIMATION Animations::GetAnimation(int id) { return AnimationsSeq[id]; }

void AnimationSets::add(int id, LPANIMATIONSET newset) { AniSeqList[id] = newset; DebugOut(L"[INFO] set added: %u\n", id);}

LPANIMATIONSET AnimationSets::GetSet(int id) { return AniSeqList[id]; }

AnimationSets* AnimationSets::GetInstance() {

	if (Instance == NULL) Instance= new AnimationSets();
	return Instance;
}


