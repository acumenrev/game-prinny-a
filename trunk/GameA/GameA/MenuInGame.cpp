#include "MenuInGame.h"

#pragma region Cosntructors & Destructor

/************************************************************************/
/*                          Constructors                                */
/************************************************************************/
CMenuInGame::CMenuInGame(void)
{
}
//////////////////////////////////////////////////////////////////////////
CMenuInGame::CMenuInGame(AllSprite* allSprite)
{
	m_allSprites = allSprite;
	m_choice = 1;
	m_menuY = 0;
	m_jumpMenu = 95; // can set later
}
/************************************************************************/
/*                          Destructor                                  */
/************************************************************************/
CMenuInGame::~CMenuInGame(void)
{
}

#pragma endregion

#pragma region Methods

/************************************************************************/
/*                          Update menu                                 */
/************************************************************************/
int CMenuInGame::Update(char keys[256], char lastKeys[256],int &currentState)
{
	// Handle event when UP key pressed
	if(KEYDOWN(keys,DIK_UP) && KEYUP(lastKeys,DIK_UP))
	{
		m_menuY -= m_jumpMenu;
		m_choice--;
	}
	// Handle event when DOWN key pressed
	if(KEYDOWN(keys,DIK_DOWN) && KEYUP(lastKeys,DIK_DOWN))
	{
		m_menuY += m_jumpMenu;
		m_choice++;
	}
	// set m_choice to 1 when its value greater than qualities of menu entries
	if(m_menuY > 2*m_jumpMenu)
	{
		m_menuY = 0;
		m_choice = 1;
	}
	// set m_choice to 3 when its value less than 0
	if(m_menuY < 0)
	{
		m_menuY = 2*m_jumpMenu;
		m_choice = 3;
	}
	// Handle event when Return key pressed
	if(KEYDOWN(keys,DIK_RETURN) && KEYUP(lastKeys,DIK_RETURN))
	{
		switch (m_choice)
		{
		case 1: // Resume
			currentState = GamePlay;
			break;
		case 2: // Save
			return 1;
			break;
		case 3: // Quit
			currentState = GameMenu;
			break;
		default:
			break;
		}
	}
	return 0;
}
/************************************************************************/
/*                          Render menu                                 */
/************************************************************************/
void CMenuInGame::Render()
{
	
	m_allSprites->m_menuInGame->Render(250,150);
	m_allSprites->m_border->Render(285,215 + m_menuY,D3DCOLOR_ARGB(150,255,255,255));
}

#pragma endregion