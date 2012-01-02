#pragma once
#include <dinput.h>
class CInput
{
public:
	CInput(void);
	~CInput(void);
	LPDIRECTINPUTDEVICE8A m_DI_Keyboard;
	LPDIRECTINPUTDEVICE8A m_DI_Mouse;
	LPDIRECTINPUT m_directInput;
	LPDIRECTINPUTDEVICE m_keyboardDevice;
	CInput(HINSTANCE hInstance,HWND hWnd);
	bool InitMouse(HINSTANCE hInstance) ;
	bool InitKeyboard(HINSTANCE hInstance,HWND hWnd);
};

