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
	m_isSaved = false;
	m_prinnyLife = 3;
	m_prinnyLifeX = 0;
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
	// Init objects list
	m_objectsList = new ListNodes();
	// Init camera
	m_camera = new CCamera();
	m_camera2 = new CCamera(100,50);
	// Init sound player
	m_bassSound = new Bass_Sound(m_hWnd);
	if(!m_bassSound)
	{
		MessageBox(NULL,"Cannot initialize Bass Sound","ERROR",MB_ICONERROR | MB_OK);
		return;
	}
	m_bassSound->Init(-1,44100,0);
	m_bassSound->AddFile(STR_MP123_OGG_WAV_AIFF,"Cut","Sounds\\Cut.wav",BASS_MUSIC_RAMPS);
	m_bassSound->SetItemVolume("Cut",50);
	m_bassSound->AddFile(STR_MP123_OGG_WAV_AIFF,"MainBackground","Sounds\\MainBackground.wav",BASS_MUSIC_RAMPS | BASS_MUSIC_LOOP);
	m_bassSound->SetItemVolume("MainBackground",100);
	m_bassSound->AddFile(STR_MP123_OGG_WAV_AIFF,"Jump","Sounds\\Jump.mp3", BASS_MUSIC_RAMPS);
	m_bassSound->SetItemVolume("Jump",100);
	m_bassSound->AddFile(STR_MP123_OGG_WAV_AIFF,"Boom","Sounds\\Boom.ogg",BASS_MUSIC_RAMPS);
	m_bassSound->SetItemVolume("Boom",100);
	m_bassSound->AddFile(STR_MP123_OGG_WAV_AIFF,"MonsterDeath","Sounds\\MonsterDeath.ogg",BASS_MUSIC_RAMPS);
	m_bassSound->SetItemVolume("MonsterDeath",50);
	m_bassSound->AddFile(STR_MP123_OGG_WAV_AIFF,"SwitchMenu","Sounds\\switchMenu.mp3",BASS_MUSIC_RAMPS);
	m_bassSound->SetItemVolume("SwitchMenu",50);
	m_bassSound->AddFile(STR_MP123_OGG_WAV_AIFF,"SelectMenu","Sounds\\SelectMenu.mp3",BASS_MUSIC_RAMPS);
	m_bassSound->SetItemVolume("SelectMenu",50);
	m_prinny = new CPrinny(0,0,40,36,m_allSprite,m_camera,m_bassSound);
	// Load Map
	m_quadTreeMap1 = new CQuadTree(SizeTile*300, SizeTile*300);
	ReadFile(m_quadTreeMap1,"Map\\Map1.txt");
	m_quadTreeMap2 = new CQuadTree(SizeTile*300, SizeTile*300);
	ReadFile(m_quadTreeMap2,"Map\\Map2.txt");
	// set m_currentMap
	m_currentMap = 1;
	Loadmap();
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
					sprintf_s(m_fps, "%s%d", "Fps: ",1000/(m_currentTime - m_lastTime));
					m_frame = 0;
				}
				SetWindowText(m_hWnd,"PEN - TNT");
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
	case GameOver:
		RenderGameOver();
		break;
	}
}
/************************************************************************/
/*                                Render Death                          */
/************************************************************************/
void CGame::RenderDeath()
{
	m_bassSound->Play("Boom",false);
	RenderGamePlay();
	int hang = 0;
	if (m_prinny->IsRight == true)
	{
		hang = 1;
	} 
	else
	{
		hang = 0;
	}

	m_allSprite->m_prinnyDeath->Render(m_prinny->x-m_camera->m_fX+m_prinny->m_width/2-21,
										m_prinny->y-m_camera->m_fY+m_prinny->m_height/2-29,
										_Rectangle(PrinnyDeathIndex*60,hang*70,60,70),D3DCOLOR_ARGB(255,255,255,255));
	PrinnyDeathIndex++;	
	Sleep(50);
	if (PrinnyDeathIndex > 8)
	{
		m_prinny->ReSpam(m_quadTree);	
		m_currentState = GamePlay;
	}
}
/************************************************************************/
/*                                Render Game play                      */
/************************************************************************/
void CGame::RenderGamePlay()
{
	//////////////////////////////////////////////////////////////////////////
	/// Background
	//////////////////////////////////////////////////////////////////////////
	Node* tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea,
			_Rectangle(m_camera->m_fX,m_camera->m_fY,WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			/*switch(tempNode->m_object->m_style)
			{

			}*/
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Background1
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera2->m_fX,
																					m_camera2->m_fY,
																					WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_BACKGROUND1:
				m_allSprite->m_background1->Render(tempNode->m_object->m_rect.left - (m_camera->m_fX*0.01),tempNode->m_object->m_rect.left - (m_camera->m_fY*0.1)-50);
				//m_allSprite->m_grass1->Render(tempNode->m_object->m_rect.left,tempNode->m_object->m_rect.top);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Background1
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera2->m_fX,
			m_camera2->m_fY,
			WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_BACKGROUND2:
				m_allSprite->m_background2->Render(tempNode->m_object->m_rect.left - (m_camera->m_fX*0.01),tempNode->m_object->m_rect.left - (m_camera->m_fY*0.1)-50);
				//m_allSprite->m_grass1->Render(tempNode->m_object->m_rect.left,tempNode->m_object->m_rect.top);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Grass
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera->m_fX,m_camera->m_fY,WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_GRASS1:
				m_allSprite->m_grass1->Render(tempNode->m_object->m_rect.left - m_camera->m_fX, tempNode->m_object->m_rect.top - m_camera->m_fY);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Grass1M2
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera->m_fX,m_camera->m_fY,WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_GRASS1M2:
				m_allSprite->m_grass1m2->Render(tempNode->m_object->m_rect.left - m_camera->m_fX, tempNode->m_object->m_rect.top - m_camera->m_fY);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Grass2M2
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera->m_fX,m_camera->m_fY,WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_GRASS2M2:
				m_allSprite->m_grass2m2->Render(tempNode->m_object->m_rect.left - m_camera->m_fX, tempNode->m_object->m_rect.top - m_camera->m_fY);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// save
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera->m_fX,m_camera->m_fY,WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_SAVE:
				if(m_isSaved == false)
				{
					m_allSprite->m_save->Render(tempNode->m_object->m_rect.left - m_camera->m_fX, tempNode->m_object->m_rect.top - m_camera->m_fY);
				}
				break;
			case UNIT_END:
				m_allSprite->m_end->Render(tempNode->m_object->m_rect.left - m_camera->m_fX-60,
					tempNode->m_object->m_rect.top - m_camera->m_fY,
					_Rectangle(tempNode->m_object->m_spriteIndex/10%4*130,0,130,112),
					D3DCOLOR_ARGB(255,255,255,255));
				tempNode->m_object->m_spriteIndex++;
				if(tempNode->m_object->m_spriteIndex >= 4*10)
				{
					tempNode->m_object->m_spriteIndex = 0;
				}
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}

	//////////////////////////////////////////////////////////////////////////
	/// Ground
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera->m_fX, m_camera->m_fY, WINDOW_WIDTH, WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_GROUND1:
				m_allSprite->m_ground1->Render(tempNode->m_object->m_rect.left - m_camera->m_fX, tempNode->m_object->m_rect.top - m_camera->m_fY);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// GroundM2
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera->m_fX, m_camera->m_fY, WINDOW_WIDTH, WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_GROUND1M2:
				m_allSprite->m_groundm2->Render(tempNode->m_object->m_rect.left - m_camera->m_fX, tempNode->m_object->m_rect.top - m_camera->m_fY);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Rock1 units
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera->m_fX, m_camera->m_fY, WINDOW_WIDTH, WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_ROCK1:
					m_allSprite->m_rock1->Render(tempNode->m_object->m_rect.left - m_camera->m_fX, tempNode->m_object->m_rect.top - m_camera->m_fY);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// RockM2 units
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, _Rectangle(m_camera->m_fX, m_camera->m_fY, WINDOW_WIDTH, WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_ROCKM2:
				m_allSprite->m_rockm2->Render(tempNode->m_object->m_rect.left - m_camera->m_fX, tempNode->m_object->m_rect.top - m_camera->m_fY);
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Fire
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, 
										_Rectangle(m_camera->m_fX, m_camera->m_fY, WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_FIRE1:
				m_allSprite->m_fire1->Render(tempNode->m_object->m_rect.left - m_camera->m_fX,
											tempNode->m_object->m_rect.top - m_camera->m_fY - 25,
											_Rectangle(tempNode->m_object->m_spriteIndex/10%4*56,29,56,83),
											D3DCOLOR_ARGB(255,255,255,255));
				tempNode->m_object->m_spriteIndex++;
				if(tempNode->m_object->m_spriteIndex >= 4*10)
				{
					tempNode->m_object->m_spriteIndex = 0;
				}
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Trap
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(tempNode->m_object->m_workingArea, 
			_Rectangle(m_camera->m_fX, m_camera->m_fY, WINDOW_WIDTH,WINDOW_HEIGHT)))
		{
			switch(tempNode->m_object->m_style)
			{
			case UNIT_TRAP:
				m_allSprite->m_trap->Render(tempNode->m_object->m_rect.left - m_camera->m_fX,
					tempNode->m_object->m_rect.top - m_camera->m_fY,
					_Rectangle(tempNode->m_object->m_spriteIndex/10%3*56,0,56,56),
					D3DCOLOR_ARGB(255,255,255,255));
				tempNode->m_object->m_spriteIndex++;
				if(tempNode->m_object->m_spriteIndex >= 3*10)
				{
					tempNode->m_object->m_spriteIndex = 0;
				}
				break;
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	//////////////////////////////////////////////////////////////////////////
	/// Other units
	//////////////////////////////////////////////////////////////////////////
	tempNode = m_objectsList->m_head;
	while(tempNode != NULL)
	{
		if(tempNode->m_object->m_style == UNIT_MONSTER1 || tempNode->m_object->m_style == UNIT_MONSTER2)
		{
			if(tempNode->m_object->m_health > 0)
			{
				if(tempNode->m_object->m_vX >= 0)
				{
					if (tempNode->m_object->m_style == UNIT_MONSTER1)
					{
						m_allSprite->m_monster1->Render(tempNode->m_object->m_rect.left - m_camera->m_fX,
							tempNode->m_object->m_rect.top - m_camera->m_fY,
							_Rectangle(tempNode->m_object->m_spriteIndex/10%5*56,168,56,56),
							D3DCOLOR_ARGB(255,255,255,255));
					}
					if (tempNode->m_object->m_style == UNIT_MONSTER2)
					{
						m_allSprite->m_monster2->Render(tempNode->m_object->m_rect.left - m_camera->m_fX,
							tempNode->m_object->m_rect.top - m_camera->m_fY,
							_Rectangle(tempNode->m_object->m_spriteIndex/10%5*56,168,56,56),
							D3DCOLOR_ARGB(255,255,255,255));
					}
					
				}
				if(tempNode->m_object->m_vX < 0)
				{
					if (tempNode->m_object->m_style == UNIT_MONSTER1)
					{
						m_allSprite->m_monster1->Render(tempNode->m_object->m_rect.left - m_camera->m_fX,
							tempNode->m_object->m_rect.top - m_camera->m_fY,
							_Rectangle(tempNode->m_object->m_spriteIndex/10%5*56,112,56,56),
							D3DCOLOR_ARGB(255,255,255,255));
					}
					if (tempNode->m_object->m_style == UNIT_MONSTER2)
					{
						m_allSprite->m_monster2->Render(tempNode->m_object->m_rect.left - m_camera->m_fX,
							tempNode->m_object->m_rect.top - m_camera->m_fY,
							_Rectangle(tempNode->m_object->m_spriteIndex/10%5*56,112,56,56),
							D3DCOLOR_ARGB(255,255,255,255));
					}
				}
				tempNode->m_object->m_spriteIndex++;
				if(tempNode->m_object->m_spriteIndex >= 10*5)
				{
					tempNode->m_object->m_spriteIndex = 0;
				}
				if(m_currentState == GamePlay || m_currentState == GameDeath)
				{
					if(CheckStayInAnotherRect(_Rectangle(m_prinny->x,m_prinny->y,m_prinny->m_width,m_prinny->m_height),tempNode->m_object->m_workingArea))
					{
						long XX = tempNode->m_object->m_rect.left;
						long YY = tempNode->m_object->m_rect.top;
						if (XX > m_prinny->x)
							tempNode->m_object->m_vX -= 0.1;
						else
							tempNode->m_object->m_vX += 0.1;
						if (tempNode->m_object->m_vX > 2)
							tempNode->m_object->m_vX = 2;
						if (tempNode->m_object->m_vX < -2)
							tempNode->m_object->m_vX = -2;
						if (YY > m_prinny->y)
							tempNode->m_object->m_vY += 0.1;
						else
							tempNode->m_object->m_vY += 0.1;
						if (tempNode->m_object->m_vY > 5)
							tempNode->m_object->m_vY = 5;

						if(!CheckRectCollideWithList(_Rectangle(XX+tempNode->m_object->m_vX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),m_objectsList)
							&& CheckCollisionBetween2Rect(_Rectangle(XX+tempNode->m_object->m_vX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),tempNode->m_object->m_workingArea))
							XX += tempNode->m_object->m_vX;
						else
							tempNode->m_object->m_vX = 0;
						if(!CheckRectCollideWithList(_Rectangle(XX,YY+tempNode->m_object->m_vY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),m_objectsList)
							||!CheckCollisionBetween2Rect(_Rectangle(XX,YY+tempNode->m_object->m_vY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),tempNode->m_object->m_workingArea))
							YY += tempNode->m_object->m_vY;
						else
							tempNode->m_object->m_vY = 0;
						tempNode->m_object->m_rect = _Rectangle(XX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight);
					}
					else
					{
						tempNode->m_object->m_vX = 0;
						tempNode->m_object->m_vY = 0;
					}
				}
			}
			else
			{	
				if(tempNode->m_object->m_spriteIndex <= 8*5)
				{
					m_bassSound->Play("MonsterDeath",false);
					m_allSprite->m_monsterDestroy->Render(tempNode->m_object->m_rect.left - m_camera->m_fX -28,tempNode->m_object->m_rect.top - m_camera->m_fY-28,
															_Rectangle(tempNode->m_object->m_spriteIndex/3%5*120,tempNode->m_object->m_spriteIndex/3/5*120,120,120),D3DCOLOR_ARGB(255,255,255,255));
					tempNode->m_object->m_spriteIndex++;
				}
			}
		}
		if(tempNode->m_object->m_style == UNIT_MONSTER3)
		{
			if(tempNode->m_object->m_health > 0)
			{
				if(tempNode->m_object->m_vX >= 0)
				{
					m_allSprite->m_monster3->Render(tempNode->m_object->m_rect.left - m_camera->m_fX,
													tempNode->m_object->m_rect.top -m_camera->m_fY+18,
													_Rectangle(tempNode->m_object->m_spriteIndex/10%8*56,58,56,58),
													D3DCOLOR_ARGB(255,255,255,255));
				}
				if(tempNode->m_object->m_vX < 0)
				{
					m_allSprite->m_monster3->Render(tempNode->m_object->m_rect.left - m_camera->m_fX,
													tempNode->m_object->m_rect.top - m_camera->m_fY+18,
													_Rectangle(tempNode->m_object->m_spriteIndex/10%8*56,0,56,58),
													D3DCOLOR_ARGB(255,255,255,255));			
				}
				tempNode->m_object->m_spriteIndex++;
				if(tempNode->m_object->m_spriteIndex >= 10*8)
				{
					tempNode->m_object->m_spriteIndex = 0;
				}
				if(m_currentState == GamePlay || m_currentState == GameDeath)
				{
					long XX = tempNode->m_object->m_rect.left;
					long YY = tempNode->m_object->m_rect.top;
					if(CheckRectCollideWithList(_Rectangle(XX+tempNode->m_object->m_vX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),m_objectsList)
						|| !CheckCollisionBetween2Rect(_Rectangle(XX+tempNode->m_object->m_vX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),tempNode->m_object->m_workingArea))
					{
						tempNode->m_object->m_vX *= -1;
						XX += tempNode->m_object->m_vX;
					}
					else
					{
						XX += tempNode->m_object->m_vX;
					}
					if(!CheckRectCollideWithList(_Rectangle(XX,YY+tempNode->m_object->m_vY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),m_objectsList)
						||!CheckCollisionBetween2Rect(_Rectangle(XX,YY+tempNode->m_object->m_vY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),tempNode->m_object->m_workingArea))
						YY += tempNode->m_object->m_vY;
					else
						tempNode->m_object->m_vY = 0;
					tempNode->m_object->m_rect = _Rectangle(XX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight);
				}
			}
			else
			{	
				if(tempNode->m_object->m_spriteIndex <= 8*5)
				{
					m_bassSound->Play("MonsterDeath",false);
					m_allSprite->m_monsterDestroy->Render(tempNode->m_object->m_rect.left - m_camera->m_fX -28,tempNode->m_object->m_rect.top - m_camera->m_fY-28,
						_Rectangle(tempNode->m_object->m_spriteIndex/3%5*120,tempNode->m_object->m_spriteIndex/3/5*120,120,120),D3DCOLOR_ARGB(255,255,255,255));
					tempNode->m_object->m_spriteIndex++;
				}
			}
		}
		if (tempNode->m_object->m_style == UNIT_CLOUD)
		{
			m_allSprite->m_cloud->Render(tempNode->m_object->m_rect.left-m_camera->m_fX,tempNode->m_object->m_rect.top-m_camera->m_fY);
			if (m_currentState == GamePlay || m_currentState == GameDeath)
			{
				if(m_currentState == GamePlay || m_currentState == GameDeath)
				{
					long XX = tempNode->m_object->m_rect.left;
					long YY = tempNode->m_object->m_rect.top;
					if(!CheckRectCollideWithList(_Rectangle(XX+tempNode->m_object->m_vX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),m_objectsList)
						|| CheckCollisionBetween2Rect(_Rectangle(XX+tempNode->m_object->m_vX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight),tempNode->m_object->m_workingArea))
					{
						XX += tempNode->m_object->m_vX;
					}
					else
					{
						tempNode->m_object->m_vX *= -1;
						XX += tempNode->m_object->m_vX;
						
					}
					if (CheckCollisionBetween2Rect(_Rectangle(m_prinny->x+5,m_prinny->y-1,m_prinny->m_width+10,m_prinny->m_height+10),tempNode->m_object->m_rect))
					{
						if(!CheckRectCollideWithList(_Rectangle(m_prinny->x+ tempNode->m_object->m_vX,m_prinny->y,m_prinny->m_width,m_prinny->m_height),m_objectsList))
						{
							m_prinny->x += tempNode->m_object->m_vX;
						}
					}
					tempNode->m_object->m_rect = _Rectangle(XX,YY,tempNode->m_object->m_iWidth,tempNode->m_object->m_iHeight);
				}
			}
		}
		tempNode = tempNode->m_nextNode;
	}
	// Render Prinny
	if (m_prinny->m_heal > 0)
	{
		if(m_prinny->x_prinnyCut < 7)
		{
			m_allSprite->m_prinny->Render(m_prinny->x-m_camera->m_fX+m_prinny->m_width/2-21,
				m_prinny->y-m_camera->m_fY+m_prinny->m_height/2-29,
				m_prinny->m_rectSpritechem,D3DCOLOR_ARGB(255,255,255,255));
			m_allSprite->m_cut->Render(m_prinny->x-m_camera->m_fX+m_prinny->m_width/2+m_prinny->TiLeRenderX-21,
				m_prinny->y-m_camera->m_fY+m_prinny->m_height/2+m_prinny->TiLeRenderY-29,
				m_prinny->m_rectSpritekiem,D3DCOLOR_ARGB(255,255,255,255));
		}
		else
		{		
			m_allSprite->m_prinny->Render(m_prinny->x-m_camera->m_fX+m_prinny->m_width/2-21,
				m_prinny->y-m_camera->m_fY+m_prinny->m_height/2-29,
				m_prinny->m_rectSprite,D3DCOLOR_ARGB(255,255,255,255));	
		}
	}	
	if(m_prinnyLife >= 0)
	{
		for(int i = 1; i<= m_prinnyLife; i++)
		{
			m_allSprite->m_life->Render(i*25,0, D3DCOLOR_ARGB(255,255,255,255));
		}
	}
	else
	{
		m_currentState = GameOver;
	}
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
		m_bassSound->SetItemVolume("MainBackground",100);
		m_bassSound->Play("MainBackground",false);
		UpdateGamePlay();
		break;
	case GameMenu:
		m_bassSound->SetItemVolume("MainBackground",0);	
		switch(m_menu->Update(m_keys,m_lastKeys,m_currentState,m_bassSound))
		{
		case 1:
			m_currentState = GamePlay;
			m_currentMap = 1;
			m_isSaved = false;
			Loadmap();
			SaveFile(m_currentMap, m_prinny->x, m_prinny->y);
			break;
		case 2:
			ReadSavedFile(m_currentMap,m_prinny->x,m_prinny->y);
			m_currentState = GamePlay;
			m_isSaved = false;
			Loadmap();
			ReadSavedFile(m_currentMap,m_prinny->x,m_prinny->y);
			break;
		}
		break;
	case GameAbout:
		m_menu->UpdateAbout(m_keys,m_lastKeys,m_currentState,m_bassSound);
		break;
	case MenuIn:
		int menuInGameChoice;
		menuInGameChoice = m_menuInGame->Update(m_keys,m_lastKeys,m_currentState,m_bassSound);
		if(menuInGameChoice == 1)
		{
			SaveFile(m_currentState,m_prinny->x,m_prinny->y);
			m_currentState = GamePlay;
		}
		break;
	case GameExit:
		PostQuitMessage(0);
		break;
	case GameOver:
		UpdateGameOver();
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
		m_currentMap++;
		if(m_currentMap > NumberOfMap)
		{
			m_currentMap = 1;
		}
		Loadmap();
		break;
	case 2:
		m_currentState = GameDeath;	
		PrinnyDeathIndex = 0;	
		m_prinnyLife--;
		break;
	case 3:
		m_currentState = MenuIn;
		break;
	case 4:
		SaveFile(m_currentState,m_prinny->x,m_prinny->y);
		break;
	case 5:
		m_currentState = GameMenu;
		break;
	}
	m_camera->SetViewPort(m_prinny->x - WINDOW_WIDTH/2 + m_prinny->m_width/2, 
						  m_prinny->y - WINDOW_HEIGHT/2 + m_prinny->m_height/2,
						 m_quadTree->m_root->m_rect.right,
						 m_quadTree->m_root->m_rect.bottom);
	m_objectsList->ResetListObject();
	m_quadTree->SetObjectsList(m_objectsList,
						_Rectangle(m_camera->m_fX, m_camera->m_fY,WINDOW_WIDTH,WINDOW_HEIGHT));
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
		m_quadTree = m_quadTreeMap2;
		break;
	default:
		break;
	}
	m_camera->m_fX = m_quadTree->m_fX;
	m_camera->m_fY = m_quadTree->m_fY;
	// load main character in here
	m_prinny = new CPrinny(m_quadTree->m_fX,m_quadTree->m_fY,36,36,m_allSprite,m_camera,m_bassSound);
	m_quadTree->SetHealth(m_quadTree->m_root);
}
/************************************************************************/
/*                            Render GameOver                           */
/************************************************************************/
void CGame::RenderGameOver()
{
	m_allSprite->m_gameOver->Render(0,0,D3DCOLOR_ARGB(255,255,255,255));
}
/************************************************************************/
/*                            Update GameOver                           */
/************************************************************************/
void CGame::UpdateGameOver()
{
	if(KEYDOWN(m_keys,DIK_RETURN)&&KEYUP(m_lastKeys,DIK_RETURN))
	{
		m_prinnyLife = 3;
		m_currentState = GameMenu;
	}
}
#pragma endregion