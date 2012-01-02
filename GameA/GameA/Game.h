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
class CGame
{
public:
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	CDXManager* m_dxManager;
	CInput* m_input;
	int m_frame;
	char m_fps[30];
	UINT64 m_currentTime;
	UINT64 m_lastTime;
	CGame(void);
	~CGame(void);
	CGame(HINSTANCE hInstance);
	bool GameInit();
	void InitObject();
	void Run();
	static LRESULT CALLBACK WndProc(HWND hWnd,UINT msg,WPARAM wParam ,LPARAM lParam);
	bool InitWindow(HINSTANCE hInstance);
	//void Loadmap();
	void Render();
	void Update();
	void UpdateGamePlay();
	void RenderGamePlay();
	void RenderDeath();
	void CreateText(char* s);
};

