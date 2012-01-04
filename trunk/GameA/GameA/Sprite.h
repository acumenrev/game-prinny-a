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
		m_prinny = new CSprite (d3ddev,"Pics\\Prinny\\Prinny.png",D3DCOLOR_ARGB(255,101,141,209));
		// BorderMenu
		m_border = new CSprite (d3ddev,"Pics\\Border.png",D3DCOLOR_ARGB(100,100,100,100));
	}
};
