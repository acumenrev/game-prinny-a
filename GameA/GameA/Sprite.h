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
	CSprite* m_monster3;
	CSprite* m_monsterDestroy;
	CSprite* m_borderMenuIn;
	CSprite* m_save;
	CSprite* m_fire1;

	CSprite* m_background2;
	CSprite* m_rockm2;
	CSprite* m_grass1m2;
	CSprite* m_grass2m2;
	CSprite* m_groundm2;
	CSprite* m_trap;
	CSprite* m_cloud;
	CSprite* m_end;
	CSprite* m_about;
	CSprite* m_life;
	CSprite* m_gameOver;
	CSprite* m_gameVictory;
	CSprite* m_newGame;
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
		// New game
		m_newGame = new CSprite(d3ddev,"Pics\\Store.PNG",D3DCOLOR_ARGB(100,100,100,100));
		//Priny
		m_prinny = new CSprite(d3ddev,"Pics\\Prinny\\Prinny.png",D3DCOLOR_ARGB(255,101,141,209));
		//Priny die
		m_prinnyDeath = new CSprite(d3ddev,"Pics\\Prinny\\die.png",D3DCOLOR_ARGB(255,0,102,102));
		// BorderMenu
		m_border = new CSprite (d3ddev,"Pics\\borderpinny.png",D3DCOLOR_ARGB(255,101,141,209));
		// border menu in
		m_borderMenuIn = new CSprite (d3ddev,"Pics\\BorderInGame.png",D3DCOLOR_ARGB(100,100,100,100));
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
		// Monster type 3
		m_monster3 = new CSprite(d3ddev,"Pics\\UNIT\\MonsterC.png",D3DCOLOR_ARGB(100,100,100,100));
		// Montser destroy
		m_monsterDestroy = new CSprite(d3ddev,"Pics\\UNIT\\Attack3.png",D3DCOLOR_ARGB(100,100,100,100));
		//save
		m_save = new CSprite(d3ddev,"Pics\\UNIT\\Save.png",D3DCOLOR_ARGB(100,100,100,100));
		// end
		m_end = new CSprite(d3ddev,"Pics\\UNIT\\finish.png",D3DCOLOR_ARGB(100,100,100,100));
		// fire 
		m_fire1 = new CSprite(d3ddev,"Pics\\UNIT\\fire.png",D3DCOLOR_ARGB(100,100,100,100));
		//
		m_trap =new CSprite(d3ddev,"Pics\\UNIT\\TrapM2.png",D3DCOLOR_ARGB(100,100,100,100));
		//
		m_background2 = new CSprite(d3ddev,"Pics\\UNIT\\Background2.png",D3DCOLOR_ARGB(100,100,100,100));

		m_rockm2 = new CSprite(d3ddev,"Pics\\UNIT\\RockM2.png",D3DCOLOR_ARGB(100,100,100,100));

		m_groundm2 = new CSprite(d3ddev,"Pics\\UNIT\\GroundM2.png",D3DCOLOR_ARGB(100,100,100,100));

		m_grass1m2 = new CSprite(d3ddev,"Pics\\UNIT\\Grass2M2.png",D3DCOLOR_ARGB(100,100,100,100));

		m_grass2m2 = new CSprite(d3ddev,"Pics\\UNIT\\Grass3M2.png",D3DCOLOR_ARGB(100,100,100,100));

		// cloud
		m_cloud = new CSprite(d3ddev,"Pics\\UNIT\\cloud.png",D3DCOLOR_ARGB(100,100,100,100));
		// about
		m_about = new CSprite(d3ddev,"Pics\\About.png",D3DCOLOR_ARGB(100,100,100,100));
		// life
		m_life = new CSprite(d3ddev,"Pics\\Heal.png",D3DCOLOR_ARGB(100,100,100,100));
		// Game Over
		m_gameOver = new CSprite(d3ddev,"Pics\\Gameover.png",D3DCOLOR_ARGB(100,100,100,100));
		// Game Victory
		m_gameVictory = new CSprite(d3ddev,"Pics\\Victory.png",D3DCOLOR_ARGB(100,100,100,100));
	}
};
