#include "CMenu.h"

#pragma region Cosntructors & Destructor

/************************************************************************/
/*                          Constructors                                */
/************************************************************************/
CCMenu::CCMenu(void)
{
}
//////////////////////////////////////////////////////////////////////////
CCMenu::CCMenu(AllSprite* allSprite)
{
	m_allSprites = allSprite;
	m_choice = 1;
	// m_jumpMenu = 95; // need to set later //60
	m_menuY = 0;
}
/************************************************************************/
/*                          Destructor                                  */
/************************************************************************/
CCMenu::~CCMenu(void)
{
}

#pragma endregion

#pragma region Methods

/************************************************************************/
/*                          Update menu                                 */
/************************************************************************/
int CCMenu::Update(char keys[256], char lastKeys[256],int &currentState)
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
	// Handle event when RETURN key pressed
	if(KEYDOWN(keys,DIK_RETURN) && KEYUP(lastKeys,DIK_RETURN))
	{
		switch(currentState)
		{
		case 1: // New Game
			return 1; // ???
			break;
		case 2: // Continue
			return 2; // ???
			break;
		case 3: // Quit
			currentState = GameExit;
			break;
		default:
			break;
		}
		return 0;
	}
	return 1;
}
/************************************************************************/
/*                          Render menu                                 */
/************************************************************************/
void CCMenu::Render()
{
	/*as->_BackMenu->Render(0,0,D3DCOLOR_ARGB(back_alpha,255,255,255));
	as->_zero_pic->Render(830+zero_X,0);
	as->_sword->Render(830+zero_X,1,D3DCOLOR_ARGB(back_alpha,r1,r2,r3));
	as->_borderTextMenu->Render(-10+bx1-delta_border+dx1,142,D3DCOLOR_ARGB(alpha_border,255,255,c1));
	as->_borderTextMenu->Render(-10+bx2-delta_border+dx2,253,D3DCOLOR_ARGB(alpha_border,255,255,c2));
	as->_borderTextMenu->Render(-10+bx3-delta_border+dx3,363,D3DCOLOR_ARGB(alpha_border,255,255,c3));

	as->_Text_menu->Render(0,142+text_y);*/
	// render background
	m_allSprites->m_backgroundMenu->Render(0,0);
	// render menu
	m_allSprites->m_menu->Render(285,235);
	// render selected region
}

#pragma endregion