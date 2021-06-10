#include <dinput.h>
#include <fstream>

#include "PlayScene.h"
#include "Utils.h"
#include "Cgame.h"
#include "Texture.h"
#include "Sprite.h"
#include "Animation.h"
#include "Brick.h"

#define MAX_GAME_LINE 1024

#define GAME_FILE_SECTION_UNKNOWN -1
#define GAME_FILE_SECTION_TEXTURES 0
#define GAME_FILE_SECTION_SPRITES 1
#define GAME_FILE_SECTION_ANIMATIONS 2
#define GAME_FILE_SECTION_ANIMATION_SETS 3
#define GAME_FILE_SECTION_OBJECTS 4

#define OBJECT_TYPE_MARIO 0
#define OBJECT_TYPE_BRICK 1
#define OBJECT_TYPE_GOOMBA 2


PlayScene::PlayScene(int id, LPCWSTR FilePath): 
	Scene(id,FilePath) {

	KeyHandler = new PlaySceneKeyHandler(this);

}

void PlayScene::Load() {

	DebugOut(L"[INFO] Start loading scene's resources from path %s \n", SceneFilePath);

	fstream s;
	s.open(SceneFilePath);

	char str[MAX_GAME_LINE];

	//Flag to change between sections
	int section = GAME_FILE_SECTION_UNKNOWN;

	while (s.getline( str, MAX_GAME_LINE)) {

		string line(str);

		if (line[0] == '#' || line == "") continue;
		else if (line == "[TEXTURES]") { section= GAME_FILE_SECTION_TEXTURES; continue; }
		else if (line == "[SPRITES]") { section = GAME_FILE_SECTION_SPRITES; continue; }
		else if (line == "[ANIMATIONS]") { section = GAME_FILE_SECTION_ANIMATIONS; continue; }
		else if (line == "[ANIMATION_SETS]") { section = GAME_FILE_SECTION_ANIMATION_SETS; continue; }
		else if (line == "[OBJECTS]") { section = GAME_FILE_SECTION_OBJECTS; continue; }
		else if (line[0] == '[') { section = GAME_FILE_SECTION_UNKNOWN; continue; }

		

		switch (section)
		{
		case GAME_FILE_SECTION_TEXTURES:
			ParseSectionTexture(line);
			break;
		case GAME_FILE_SECTION_SPRITES:
			ParseSectionSprites(line);
			break;
		case GAME_FILE_SECTION_ANIMATIONS:
			ParseSectionAnimations(line);
			break;
		case GAME_FILE_SECTION_ANIMATION_SETS:
			ParseSectionAnimationSets(line);
			break;
		case GAME_FILE_SECTION_OBJECTS:
			ParseSectionObjects(line);
			break;
		default:
			break;
		}
	}

}

void PlayScene::Update(DWORD dt) {

	vector<LPGAMEOBJECT> coObjects;

	for (int i = 1; i < GameObject.size(); i++) coObjects.push_back(GameObject[i]);  // List of colliable objects

	for (int i = 0; i < GameObject.size(); i++) GameObject[i]->Update(dt,&coObjects); //Update object and detect collision.

}

void PlayScene::Unload() {

	for (int i = 0; i < GameObject.size(); i++)
		delete GameObject[i];

	GameObject.clear();
	Player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", SceneFilePath);

}

void PlayScene::Render() {
	

	for (int i = 0; i < GameObject.size(); i++) GameObject[i]->Render();

}

void PlayScene::ParseSectionTexture(string line) {

	vector<string> tokens = split(line);

	if (tokens.size() < 5) return;

	Textures* texture = Textures::GetInstance();
	
	texture->Add(atoi(tokens[0].c_str()), ToLPCWSTR(tokens[1]), D3DCOLOR_XRGB(atoi(tokens[2].c_str()),atoi(tokens[3].c_str()),atoi(tokens[4].c_str())));

}

void PlayScene::ParseSectionSprites(string line) {

	vector<string> tokens = split(line);
	if (tokens.size() < 6) return;

	Textures* texs = Textures::GetInstance();
	LPDIRECT3DTEXTURE9 tex = texs->GetTexture(atoi(tokens[5].c_str()));
	Sprites::GetInstance()->add(
		atoi(tokens[0].c_str()),                  //ID
		atoi(tokens[1].c_str()),                  //left
		atoi(tokens[2].c_str()),                  //top
		atoi(tokens[3].c_str()),                  //right
		atoi(tokens[4].c_str()),                  //bottom
		tex  //tex's ID
	);
}

void PlayScene::ParseSectionAnimations(string line) {

	vector<string> tokens = split(line);

	if ((tokens.size()-1) % 2 != 0 || tokens.size()==1) {
		DebugOut(L"[ERROR] Corrupted Animation info\n ");
		DebugOut(L"--> %s\n",ToWSTR(line).c_str());
		return;
	}

	LPANIMATION newani = new Animation();
	for (int i = 1; i < tokens.size(); i += 2) {

		newani->Add(atoi(tokens[i].c_str()), atoi(tokens[i + 1].c_str()));
	}
	Animations::GetInstance()->add(atoi(tokens[0].c_str()), newani);

}

void PlayScene::ParseSectionAnimationSets(string line) {

	vector<string> tokens = split(line);

	if (tokens.size() < 2) {
		DebugOut(L"Corrupted Animation Sets section\n");
		return;
	}

	AnimationSet* newAniSet = new AnimationSet();

	for (int i = 1; i < tokens.size(); i++) {

		int id = atoi(tokens[i].c_str());
		newAniSet->push_back(Animations::GetInstance()->GetAnimation(id));
		DebugOut(L"[INFO] set pushes back id:%u \n", id );
	}
	
	AnimationSets::GetInstance()->add(atoi(tokens[0].c_str()),newAniSet);
}

void PlayScene::ParseSectionObjects(string line) {

	vector<string> tokens = split(line);

	if (tokens.size() < 3) return;

	int type = atoi(tokens[0].c_str());

	LPGAMEOBJECT obj = NULL;

	switch (type)
	{
	case OBJECT_TYPE_MARIO:
		if (this->GetPlayer() != NULL) {
			DebugOut(L"Mario has already been created\n");
			return;
		}
		else {
			obj = new Mario();
			Player =(Mario*) obj;
		}
		break;
	case OBJECT_TYPE_BRICK:
		obj = new Brick();
		break;
	case OBJECT_TYPE_GOOMBA:
		break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", type);
		return;
	}

	obj->setLocation(atof(tokens[1].c_str()), atof(tokens[2].c_str()));
	obj->setVelocity(0, 0);
	obj->setAnimationSet(AnimationSets::GetInstance()->GetSet(atoi(tokens[3].c_str())));
	GameObject.push_back(obj);

}

void PlayScene::clear() {}

void PlaySceneKeyHandler::OnKeyDown(int KeyCode) {

	DebugOut(L"[INFO] KeyDown %d\n", KeyCode);

	Mario* mario = ((PlayScene*)Scene)->GetPlayer();
	switch (KeyCode)
	{
	case DIK_SPACE:
		mario->setState(MARIO_STATE_JUMP);
		break;
	default:
		break;
	}
}

void PlaySceneKeyHandler::KeyState(BYTE* states) {

	Cgame* game = Cgame::GetInstance();
	Mario* mario = ((PlayScene*)Scene)->GetPlayer();
	if (mario->GetState() == MARIO_STATE_DIE) return;
	else if (game->IsKeyDown(DIK_LEFT)) if (mario->GetVelocity_x() > 0) mario->setState(MARIO_STATE_BREAK_LEFT);
	else mario->setState(MARIO_STATE_WALK_LEFT);
	else if (game->IsKeyDown(DIK_RIGHT)) if (mario->GetVelocity_x() < 0) mario->setState(MARIO_STATE_BREAK_RIGHT);
	else mario->setState(MARIO_STATE_WALK_RIGHT);
	else if (game->IsKeyDown(DIK_DOWN)) mario->setState(MARIO_STATE_DIVE);
	else mario->setState(MARIO_STATE_IDLE);
}

//void PlaySceneKeyHandler::OnKeyUp(int KeyCode) {
//
//	DebugOut(L"[INFO] KeyUp %d\n", KeyCode);
//
//	Mario* mario = ((PlayScene*)Scene)->GetPlayer();
//	switch (KeyCode)
//	{
//	case DIK_SPACE:
//		/*mario->setState(MARIO_STATE_JUMP);*/
//		break;
//	default:
//		break;
//	}
//}