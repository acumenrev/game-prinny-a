#pragma once
#include<windows.h>
#include<d3d9.h>
#include<d3dx9.h>
#include<ddraw.h>
#include<atltime.h>
#include<time.h>
#include <string.h>
#include "DXManager.h"
#include "Input.h"
#include "CObject.h"
#include "Information.h"
#include "Position.h"
#include "Sprite.h"
#include "CMenu.h"
#include "MenuInGame.h"
#include "Collision.h"
#include "CPrinny.h"
class CGame
{
public:
	/************************************************************************/
	/*                             Variables                                */
	/************************************************************************/
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	CDXManager* m_dxManager;
	CInput* m_input;
	int m_frame;
	char m_fps[30];
	char m_keys[256];
	char m_lastKeys[256];
	UINT64 m_currentTime;
	UINT64 m_lastTime;
	AllSprite* m_allSprite;
	int m_currentState;
	CCMenu* m_menu;
	CMenuInGame* m_menuInGame;
	CCObject* m_object;
	CPrinny* m_prinny;
	CCamera* m_camera;
	/************************************************************************/
	/*                     Constructors & Destructor                        */
	/************************************************************************/
	CGame(void);
	~CGame(void);
	CGame(HINSTANCE hInstance);
	/************************************************************************/
	/*                           Methods							        */
	/************************************************************************/
	bool GameInit();
	void InitObject();
	void Run();
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam ,LPARAM lParam);
	bool InitWindow(HINSTANCE hInstance);
	//void Loadmap();
	void Render();
	void Update();
	void UpdateGamePlay(/*char keys[256]/ *, char lastKeys[256]* /*/);
	void RenderGamePlay();
	void RenderDeath();
};

