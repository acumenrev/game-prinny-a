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
	m_object = new CCObject(100,100,NULL);
	// set m_currentMap
	m_currentMap = 1;
	// Init camera
	m_camera = new CCamera();
	m_prinny = new CPrinny(0,0,56,56,m_allSprite,m_camera);
}
/************************************************************************/
/*                             Run game                                 */
/************************************************************************/
void CGame::Run()
{
	MSG msg;
	ZeroMemory(&msg,sizeof(msg));
	UINT64 countPerSecond = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countPerSecond);
	float secondPerCount = 1.0f/ (float)countPerSecond;
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
			if((m_currentTime - m_lastTime) > 14)
			{
				Update();
				m_dxManager->ClearScreen();
				m_dxManager->BeginDraw();
				Render();
				//itoa(1000/(a-b), fps, 10);
				if(m_frame == 5)
				{
					//sprintf_s(m_fps, "%s%d", "Fps: ", 1000/(m_currentTime - m_lastTime));
					sprintf_s(m_fps, "%s%d", "Fps: ",1000/(m_currentTime - m_lastTime));
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
	RenderGamePlay();

}
/************************************************************************/
/*                                Render Game play                      */
/************************************************************************/
void CGame::RenderGamePlay()
{
		int index_sprite = m_object->m_spriteIndex;
		m_allSprite->m_prinny->Render(350+m_prinny->x,250+m_prinny->y,m_prinny->m_rectSprite,D3DCOLOR_ARGB(255,255,255,255));
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
	switch(m_prinny->Update(m_keys,m_lastKeys,m_quadTree))
	{
	case 1:
		break;
	case 2:
		RenderDeath();
		break;
	case 3:
		m_currentState = MenuIn;
		break;
	}
	m_camera->SetViewPort(m_prinny->x - WINDOW_WIDTH,m_prinny->y - WINDOW_HEIGHT,3000,2000);
}
/************************************************************************/
/*                             Load Map                                 */
/************************************************************************/
void CGame::Loadmap()
{
	switch (m_currentMap)
	{
	case 1:
		m_quadTree = m_quadTreeMap1;
		break;
	case 2:
		m_quadTree = m_quadTreeeMap2;
		break;
	default:
		break;
	}
	m_camera->m_fX = m_quadTree->m_fX;
	m_camera->m_fY = m_quadTree->m_fY;
	// load main character in here
	// .....
	// ,,,,,
	// .....
	// Set health for enemies
	m_quadTree->SetHealth(m_quadTree->m_root);
}
#pragma endregion