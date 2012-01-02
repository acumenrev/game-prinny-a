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
	w.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
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
	return true;
}
/************************************************************************/
/*                               Init objects                           */
/************************************************************************/
void CGame::InitObject()
{
}
/************************************************************************/
/*                                Render                                */
/************************************************************************/
void CGame::Render()
{

}
/************************************************************************/
/*                                Render Death                          */
/************************************************************************/
void CGame::RenderDeath()
{

}
/************************************************************************/
/*                                Render Gameplay                       */
/************************************************************************/
void CGame::RenderGamePlay()
{

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
					sprintf(m_fps, "%s%d", "Fps: ", 1000/(m_currentTime - m_lastTime));
					m_frame = 0;
				}
				//CreateText(m_fps);
				SetWindowText(m_hWnd,m_fps);
				m_frame++;
				m_dxManager->EndDraw();
				m_lastTime = m_currentTime;
			}
		}
	}
}
/************************************************************************/
/*                                 Update                               */
/************************************************************************/
void CGame::Update()
{

}
/************************************************************************/
/*                                Update Gameplay                       */
/************************************************************************/
void CGame::UpdateGamePlay()
{

}
/************************************************************************/
/*                                Create text on window                 */
/************************************************************************/
void CGame::CreateText(char* s)
{
	ID3DXFont* m_font;	
	D3DXCreateFont(
		m_dxManager->m_directXDevice,
		20,
		0,
		FW_BOLD,
		0,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Arial"),
		&m_font);
	D3DCOLOR fontColor = D3DCOLOR_ARGB(255,255,255,255);
	// Create a rectangle indicate where on the screen it should be drawn
	RECT rect;
	rect.left = 2;
	rect.right = 450;
	rect.top = 10;
	rect.bottom = rect.top + 20;
	// Draw some text
	m_font->DrawTextA(NULL,s,-1,&rect,0,fontColor);
}
#pragma endregion