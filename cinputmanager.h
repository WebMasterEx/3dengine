#pragma once

#include <Windows.h>
#include <dinput.h>

#include "keyboard.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")



struct MousePositionState {
	MousePositionState() : x(0), y(0) {
	};

	float x, y, z;
};

struct MouseState {
	MouseState() : isLeftPressed(false), isRightPressed(false), isMiddlePressed(false) {
	
	};

	bool isLeftPressed, isRightPressed, isMiddlePressed;
	MousePositionState position;
};

class CInputManager {
public:
	CInputManager();
	~CInputManager();

	HRESULT Initialize(HWND hWnd);
	void Shutdown();

	void Update();

	bool isKeyPressed(BYTE key);
	//bool isKeyDown();
	//bool isKeyUp();

	//bool isMouseLeftPressed();
	//bool isMouseRightPressed();
	//bool isMouseMiddlePressed();
	//const MousePositionState* getMousePosition();
	//const MouseState* getMouseState();

	float getMouseX();
	float getMouseY();
	float getMouseZ();

protected:
	HWND m_hWnd;
	MouseState* m_MouseState;

	IDirectInput8* m_DInput;
	IDirectInputDevice8* m_Keyboard;
	IDirectInputDevice8* m_Mouse;

	BYTE m_Keys[256];
	DIMOUSESTATE2 m_DInputMouseState;
};