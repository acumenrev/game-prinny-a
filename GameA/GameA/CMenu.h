#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Information.h"
#include "Sprite.h"
#include "Input.h"

class CCMenu
{
public:
	/************************************************************************/
	/*                              Variables                               */
	/************************************************************************/
	AllSprite* m_allSprite;
	int m_choice;
	int m_jumpMenu;		// distance between 2 menu entries
	int m_menuY;		// selected region's y-coordinate
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
	int Update(char keys[256], char lastKeys[256],int &currentState);
};

