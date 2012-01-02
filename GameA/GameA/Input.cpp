#include "Input.h"

#pragma region Constructors & Destructor

/************************************************************************/
/*                            Constructor                               */
/************************************************************************/
CInput::CInput(void)
{
}
/************************************************************************/
/*                            Destructor                                */
/************************************************************************/
CInput::~CInput(void)
{
}
/************************************************************************/
/*                            Constructor                               */
/************************************************************************/
CInput::CInput(HINSTANCE hInstance,HWND hWnd)
{
	m_directInput=NULL;
	m_keyboardDevice=NULL;
	//initialize keyboard
	if(!InitKeyboard(hInstance,hWnd))
	{
		MessageBox(hWnd,"cannot initialize keyboard device ","Error",MB_OK);
	}
	if(!InitMouse(hInstance))
	{
		MessageBox(hWnd,"Cannot initialize mouse device ","Error",MB_OK);
	}
}

#pragma endregion 

#pragma region Methods
/************************************************************************/
/*                            Init Keyboard                             */
/************************************************************************/
bool CInput::InitKeyboard(HINSTANCE hInstance,HWND hWnd)
{
	HRESULT result; 
	LPDIRECTINPUT8 DI_Object;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DI_Object, NULL); 
	if (result != DI_OK) 
	{
		return 0;
	}
	DI_Object->CreateDevice(GUID_SysKeyboard, &m_DI_Keyboard, NULL); 
	result = m_DI_Keyboard->SetDataFormat(&c_dfDIKeyboard);
	result = m_DI_Keyboard->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 
	result = m_DI_Keyboard->Acquire();
	return 1;
}
/************************************************************************/
/*                             Init Mouse                               */
/************************************************************************/
bool CInput::InitMouse(HINSTANCE hInstance)
{
	HRESULT result; 
	LPDIRECTINPUT8 DI_Object;
	result = DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&DI_Object, NULL); 
	if (result != DI_OK) 
	{
		return false;
	}
	DI_Object->CreateDevice(GUID_SysMouse, &m_DI_Mouse, NULL); 
	result = m_DI_Mouse->SetDataFormat(&c_dfDIMouse);
	result = m_DI_Mouse->Acquire();
	return true;
}

#pragma endregion 