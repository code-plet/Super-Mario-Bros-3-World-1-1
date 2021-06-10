#pragma once
#include <Windows.h>

class CKeyEventHandler{

public:
	virtual void KeyState(BYTE* states) = 0;
	virtual void OnKeyDown(int Keycode) = 0;
	virtual void OnKeyUp(int keycode) = 0;

};
typedef CKeyEventHandler* LPKEYEVENTHANDLER;
