#pragma once
#pragma comment(lib,"bass.lib")
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
#include "QuadTree.h"
#include "CFile.h"
#include "Camera.h"
#include "Bass_Sound.h"
using namespace WaZ_Game_App;
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
	int PrinnyDeathIndex;
	int m_currentState;
	int m_currentMap;
	CCMenu* m_menu;
	CMenuInGame* m_menuInGame;
	CCObject* m_object;
	CQuadTree* m_quadTree;
	CQuadTree* m_quadTreeMap1;
	CQuadTree* m_quadTreeMap2;
	CCamera* m_camera;
	CCamera* m_camera2;
	CPrinny* m_prinny;
	Bass_Sound* m_bassSound;
	ListNodes* m_objectsList;
	int m_id;
	bool m_isSaved;
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
	void Loadmap();
	void Render();
	void Update();
	void UpdateGamePlay();
	void RenderGamePlay();
	void RenderDeath();
};

