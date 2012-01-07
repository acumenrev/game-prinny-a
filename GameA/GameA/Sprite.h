#pragma once
#include"d3dx9.h"
#include"d3d9.h"
#include "Information.h"
class CSprite
{
public:
	// variables
	LPD3DXSPRITE m_spriteHandler;
	LPDIRECT3DTEXTURE9 m_texture;
	D3DXIMAGE_INFO m_info;
	CSprite(void);
	~CSprite(void);
	CSprite(LPDIRECT3DDEVICE9 d3ddev, char* fileName, D3DCOLOR color);
	void Render(float fX, float fY);
	void Render(float fX, float fY, D3DCOLOR color);
	void Render(float fX, float fY, RECT rect, D3DCOLOR color);
	void Render(float fX, float fY, RECT rect, D3DCOLOR color, float rotate);
	void Render(float fX, float fY, RECT rect, D3DCOLOR color, float rotate, float Xscaling, float yScaling);
};

class AllSprite
{
public:
	/************************************************************************/
	/*                               Variables                              */
	/************************************************************************/
	
	CSprite* m_menu;
	CSprite* m_menuInGame;
	CSprite* m_backgroundMenu;
	CSprite* m_prinny;
	CSprite* m_border;
	CSprite* m_prinnyDeath;
	CSprite* m_cut;
	CSprite* m_grass1;
	CSprite* m_ground1;
	CSprite* m_background1;
	CSprite* m_rock1;
	CSprite* m_monster1;
	CSprite* m_monster2;
	/************************************************************************/
	/*                               Constructor                            */
	/************************************************************************/

	AllSprite(LPDIRECT3DDEVICE9 d3ddev)
	{
		/************************************************************************/
		/*                            All sprites			                    */
		/************************************************************************/

		// Main menu
		m_menu = new CSprite(d3ddev,"Pics\\Menu.PNG",D3DCOLOR_ARGB(100,100,100,100)); 
		// Background in GameMenu
		m_backgroundMenu = new CSprite(d3ddev,"Pics\\MenuBG.PNG",D3DCOLOR_ARGB(100,100,100,100));
		// Menu in game
		m_menuInGame = new CSprite(d3ddev,"Pics\\MenuInGame.PNG",D3DCOLOR_ARGB(100,100,100,100));
		//Priny
		m_prinny = new CSprite(d3ddev,"Pics\\Prinny\\Prinny.png",D3DCOLOR_ARGB(255,101,141,209));
		//Priny die
		m_prinnyDeath = new CSprite(d3ddev,"Pics\\Prinny\\die.png",D3DCOLOR_ARGB(255,0,102,102));
		// BorderMenu
		m_border = new CSprite (d3ddev,"Pics\\Border.png",D3DCOLOR_ARGB(100,100,100,100));
		// cut
		m_cut = new CSprite (d3ddev,"Pics\\Prinny\\Chem.png",D3DCOLOR_ARGB(100,100,100,100));
		// Grass 
		m_grass1 = new CSprite(d3ddev,"Pics\\UNIT\\grass.png",D3DCOLOR_ARGB(100,100,100,100));
		// Ground
		m_ground1 = new CSprite(d3ddev,"Pics\\UNIT\\BreakBrick.png",D3DCOLOR_ARGB(100,100,100,100));
		//background1
		m_background1 = new CSprite(d3ddev,"Pics\\UNIT\\Background1.png",D3DCOLOR_ARGB(100,100,100,100));
		//Rock 1
		m_rock1 = new CSprite(d3ddev,"Pics\\UNIT\\ROCK.png",D3DCOLOR_ARGB(100,100,100,100));
		// Monster type 1
		m_monster1 = new CSprite(d3ddev,"Pics\\UNIT\\Monster.png",D3DCOLOR_ARGB(100,100,100,100));
		// Monster type 2
		m_monster2 = new CSprite(d3ddev,"Pics\\UNIT\\MonsterB.png",D3DCOLOR_ARGB(100,100,100,100));
	}
};
