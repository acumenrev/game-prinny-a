#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Information.h"
#include "Sprite.h"
#include "Input.h"
#include "Collision.h"
#include "CObject.h"
#include "Bass_Sound.h"
class CCMenu
{
public:
	/************************************************************************/
	/*                              Variables                               */
	/************************************************************************/
	AllSprite* m_allSprites;
	int m_choice;
	int m_jumpMenu;		// distance between 2 menu entries
	int m_menuY;		// selected region's y-coordinate
	CCObject* m_object;
	/************************************************************************/
	/*                          Constructor & Destructor                    */
	/************************************************************************/
	CCMenu(void);
	~CCMenu(void);
	CCMenu(AllSprite* allSprite);
	/************************************************************************/
	/*                           Methods                                    */
	/************************************************************************/
	void Render();
	void RenderAbout();
	int Update(char keys[256], char lastKeys[256],int &currentState, WaZ_Game_App::Bass_Sound* bassSound);
	int UpdateAbout(char keys[256], char lastKeys[256],int &currentState);
	int GetUpdate();
};

