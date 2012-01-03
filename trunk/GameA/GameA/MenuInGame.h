#pragma once
#include <d3d9.h>
#include <windows.h>
#include <d3dx9.h>
#include "Information.h"
#include "Input.h"
#include "Sprite.h"
class CMenuInGame
{
public:
	/************************************************************************/
	/*                              Variables                               */
	/************************************************************************/
	AllSprite* m_allSprites; // all sprites
	int m_choice; 
	int m_jumpMenu; // distance between 2 menu entries
	int m_menuY;   // menu's y-coordinate
	/************************************************************************/
	/*                          Constructor & Destructor                    */
	/************************************************************************/
	CMenuInGame(void);
	~CMenuInGame(void);
	CMenuInGame(AllSprite* allSprite);
	/************************************************************************/
	/*                           Methods                                    */
	/************************************************************************/
	void Render();
	int Update(char keys[256], char lastKeys[256],int &currentState);
};

