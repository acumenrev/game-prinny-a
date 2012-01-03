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
	m_jumpMenu = 60; // need to set later //60
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
	if(m_menuY > 3*m_jumpMenu)
	{
		m_menuY = 0;
		m_choice = 1;
	}
	// set m_choice to 4 when its value less than 0
	if(m_menuY < 0)
	{
		m_menuY = 3*m_jumpMenu;
		m_choice = 4;
	}
	// Handle event when RETURN key pressed
	if(KEYDOWN(keys,DIK_RETURN) && KEYUP(lastKeys,DIK_RETURN))
	{
		switch(m_choice)
		{
		case 1: // New Game
			return 1; // ???
			break;
		case 2: // Continue
			return 2; // ???
			break;
		case 3: // About
			currentState = GameAbout;
			break;
		case 4: // Quit
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
	m_allSprites->m_border->Render(270,(float)(m_menuY+260));
	m_allSprites->m_menu->Render(275,235);
	// render selected region

}
/************************************************************************/
/*                          Render About                                */
/************************************************************************/
void CCMenu::RenderAbout()
{
	CCollision* m_rect = new CCollision();
	// render background
	m_allSprites->m_backgroundMenu->Render(0,0);
	// sprite
	m_allSprites->m_prinny->Render(350,250,m_rect->_Rectangle(0,0,41,46),D3DCOLOR_ARGB(255,255,255,255));

}
/************************************************************************/
/*                           Update About                               */
/************************************************************************/
int CCMenu::UpdateAbout(char keys[256], char lastKeys[256],int &currentState)
{
	if(KEYDOWN(keys,DIK_RETURN) && KEYUP(lastKeys,DIK_RETURN))
	{
		currentState = GameMenu;
		return 1;
	}
	return 1;
}
#pragma endregion