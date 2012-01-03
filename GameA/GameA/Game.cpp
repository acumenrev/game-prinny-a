#include "Game.h"

#pragma region Constructors & Destructor

/************************************************************************/
/*                              Constructor                             */
/************************************************************************/
CGame::CGame(void)
{
}
/************************************************************************/
/*                              Destructor                              */
/************************************************************************/
CGame::~CGame(void)
{
}
/************************************************************************/
/*                              Constructor                             */
/************************************************************************/
CGame::CGame(HINSTANCE hInstance)
{
	m_hInstance = hInstance;
	m_dxManager = new CDXManager();
	m_currentTime = 0;
	m_lastTime = 0;
	m_frame = 0;
}

#pragma endregion 

#pragma region Methods

//////////////////////////////////////////////////////////////////////////
//																		//
//							WINDOW										//
//																		//
//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*                      Window Initialization                           */
/************************************************************************/
bool CGame::InitWindow(HINSTANCE hInstance)
{
	WNDCLASS w;
	w.cbClsExtra = 0;
	w.cbWndExtra = 0;
	w.lpfnWndProc = (WNDPROC)WndProc;
	w.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	w.hCursor = LoadCursor(NULL,IDC_ARROW);
	w.hIcon = NULL;
	w.lpszClassName = APPNAME;
	w.lpszMenuName = NULL;
	w.style = CS_HREDRAW|CS_VREDRAW;
	w.hInstance = hInstance;
	if(!RegisterClass(&w))
		return false;
	// Windows Constructor
	m_hWnd=CreateWindow
		(
		APPNAME,
		APPNAME,
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		WINDOW_WIDTH,
		WINDOW_HEIGHT,
		NULL,
		NULL,
		hInstance,
		NULL
		);
	if(m_hWnd == NULL)
	{
		return false;
	}
	ShowWindow(m_hWnd,SW_SHOW);
	UpdateWindow(m_hWnd);
	return true;
}
/************************************************************************/
/*                       Process Window Event                           */
/************************************************************************/
LRESULT CALLBACK CGame::WndProc(HWND hWnd,UINT msg,WPARAM wParam ,LPARAM lParam)
{
	switch(msg)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
		switch(wParam)
		{
		case VK_ESCAPE:
			int e = MessageBox(NULL,"Quit program ?","",MB_YESNO | MB_ICONQUESTION);
			if(e==IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;
		}
		return 0;
	case WM_QUIT:
		DestroyWindow(hWnd);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}
/************************************************************************/
/*                       Game Initialization                            */
/************************************************************************/
bool CGame::GameInit()
{
	if(!InitWindow(m_hInstance))
	{
		MessageBox(NULL,"Cannot initialize window","ERROR",MB_OK | MB_ICONERROR);
		return false;
	}
	if(!m_dxManager->InitDirectX(m_hWnd))
	{
		MessageBox(NULL,"Cannot initialize DirectX","ERROR",MB_OK | MB_ICONERROR);
		return false;
	}
	// keyboard
	m_input = new CInput(m_hInstance,m_hWnd);
	InitObject();
	return true;
}
/************************************************************************/
/*                               Init objects                           */
/************************************************************************/
void CGame::InitObject()
{
	// Init all sprites
	m_allSprite = new AllSprite(m_dxManager->m_directXDevice);
	// Render menu when begin game
	m_currentState = GameMenu;
	m_menuInGame = new CMenuInGame(m_allSprite);
	m_menu = new CCMenu(m_allSprite);
}
/************************************************************************/
/*                             Run game                                 */
/************************************************************************/
void CGame::Run()
{
	MSG msg;
	ZeroMemory(&msg,sizeof(msg));
	while(msg.message!=WM_QUIT)
	{
		if(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			m_currentTime = GetTickCount();
			if(m_currentTime - m_lastTime > 14)
			{
				Update();
				m_dxManager->ClearScreen();
				m_dxManager->BeginDraw();
				Render();
				//itoa(1000/(a-b), fps, 10);
				if(m_frame == 10)
				{
					//float temp = (float)(1000/(m_currentTime - m_lastTime));
					sprintf_s(m_fps, "%s%d", "Fps: ", 1000/(m_currentTime - m_lastTime));
					m_frame = 0;
				}
				SetWindowText(m_hWnd,m_fps);
				m_frame++;
				m_dxManager->EndDraw();
				m_lastTime = m_currentTime;
			}
		}
	}
}
/************************************************************************/
/*                                Render                                */
/************************************************************************/
void CGame::Render()
{
	switch(m_currentState)
	{
	case GamePlay:
		RenderGamePlay();
		break;
	case GameDeath:
		RenderDeath();
		break;
	case GameMenu:
		m_menu->Render();
		break;
	case GameAbout:
		m_menu->RenderAbout();
		break;
	case MenuIn:
		RenderGamePlay();
		m_menuInGame->Render();
		break;
	}
}
/************************************************************************/
/*                                Render Death                          */
/************************************************************************/
void CGame::RenderDeath()
{

}
/************************************************************************/
/*                                Render Game play                      */
/************************************************************************/
void CGame::RenderGamePlay()
{
	
}

/************************************************************************/
/*                                 Update                               */
/************************************************************************/
void CGame::Update()
{
	m_input->m_DI_Keyboard->GetDeviceState(sizeof(m_keys),&m_keys);
	switch(m_currentState)
	{
	case GamePlay:
		UpdateGamePlay();
		break;
	case GameDeath:
		break;
	case GameMenu:
		m_menu->Update(m_keys,m_lastKeys,m_currentState);
		//int mainMenuChoice;
		//mainMenuChoice = m_menu->Update(m_keys,m_lastKeys,m_currentState);
		//if(mainMenuChoice == 1) // New Game
		//{
		//	m_currentState = GamePlay;
		//	// Load map
		//}
		//if(mainMenuChoice == 2) // Continue
		//{
		//	// Read saved file
		//	m_currentState = GamePlay;
		//	// Load map
		//}
		break;
	case GameAbout:
		m_menu->UpdateAbout(m_keys,m_lastKeys,m_currentState);
		break;
	case MenuIn:
		int menuInGameChoice;
		menuInGameChoice = m_menuInGame->Update(m_keys,m_lastKeys,m_currentState);
		if(menuInGameChoice == 1)
		{
			// Save file
			m_currentState = GamePlay;
		}
		break;
	case GameExit:
		PostQuitMessage(0);
		break;
	}
	m_input->m_DI_Keyboard->GetDeviceState(sizeof(m_keys),&m_lastKeys);
}
/************************************************************************/
/*                                Update Game play                      */
/************************************************************************/
void CGame::UpdateGamePlay()
{

}

#pragma endregion