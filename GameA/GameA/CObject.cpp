#include "CObject.h"

/************************************************************************/
/*                           Constructor                                */
/************************************************************************/
CCObject::CCObject(void)
{
	m_fx = 0;
	m_fy = 0;
	m_iHeight = 0;
	m_iWidth = 0;
}
/************************************************************************/
/*                           Destructor                                 */
/************************************************************************/
CCObject::~CCObject(void)
{
}
/************************************************************************/
/*                           Constructor                                */
/************************************************************************/
CCObject::CCObject(float fX, float fY, char style)
{
	m_rotate = 0;
	m_scale = 1;
	m_vX = 0;
	m_vY = 0;
	m_workingArea = _Rectangle(fX,fY,SizeTile,SizeTile);
	m_canCollide = false;
	m_canBeDestroyed = false;
	m_checkedItem = false;
	m_spriteIndex = 0;
	switch(style)
	{
	// set m_rect in here due to Unit
	case UNIT_STATIC:
		m_canCollide = true;
		m_rect = _Rectangle(fX, fY, SizeTile*2, SizeTile *2);
		m_workingArea = _Rectangle(fX, fY, SizeTile*2, SizeTile*2);
		break;
	// Grass
	case UNIT_GRASS1:
		m_rect = _Rectangle(fX, fY, SizeTile*14, SizeTile*5);
		m_workingArea = _Rectangle(fX, fY, SizeTile*14, SizeTile*5);
		break;
	// Ground
	case UNIT_GROUND1:
		m_canCollide = true;
		m_rect = _Rectangle(fX, fY, SizeTile*11, SizeTile);
		m_workingArea = _Rectangle(fX, fY, SizeTile*11, SizeTile);
		break;
	// Background
	case UNIT_BACKGROUND1:
		m_rect = _Rectangle(fX, fY, SizeTile*20, SizeTile*10);
		m_workingArea = _Rectangle(fX, fY, SizeTile*500, SizeTile*100);
		break;
	case UNIT_BACKGROUND2:
		m_rect = _Rectangle(fX, fY, SizeTile*20, SizeTile*10);
		m_workingArea = _Rectangle(fX, fY, SizeTile*500, SizeTile*100);
		break;
	case UNIT_ROCK1:
		m_canCollide = true;
		m_canBeDestroyed = false;
		m_checkedItem = false;
		m_rect = _Rectangle(fX, fY, SizeTile*1, SizeTile*1);
		m_workingArea = _Rectangle(fX, fY, SizeTile*1, SizeTile*1);
		break;
	// others
	case UNIT_SAVE:
		m_canCollide = false;
		m_checkedItem = true;
		m_rect = _Rectangle(fX, fY, 52, 81);
		m_workingArea = _Rectangle(fX, fY, SizeTile*1, SizeTile*2);
		break;
	case UNIT_BEGIN:
		m_canCollide = false;
		break;
	case UNIT_END:
		m_canCollide = false;
		m_checkedItem = true;
		m_rect = _Rectangle(fX, fY,130, 112);
		m_workingArea = _Rectangle(fX, fY, SizeTile, SizeTile);
		break;
	/// Monster
	case UNIT_MONSTER1:
		m_canCollide = false;
		m_checkedItem = true;
		m_canBeDestroyed = true;
		m_rect = _Rectangle(fX, fY, 40, 40);
		m_workingArea = _Rectangle(fX-SizeTile*10, fY-SizeTile*10, SizeTile*20, SizeTile*20);
		m_vX = 0;
		m_vY = 0;
		break;
	case UNIT_MONSTER2:
		m_canCollide = false;
		m_checkedItem = true;
		m_canBeDestroyed = true;
		m_rect = _Rectangle(fX, fY, 40, 40);
		m_workingArea = _Rectangle(fX-SizeTile*10, fY-SizeTile*10, SizeTile*20, SizeTile*20);
		m_vX = 2;
		m_vY = 0;
		break;
	case UNIT_MONSTER3:
		m_canCollide = false;
		m_checkedItem = true;
		m_canBeDestroyed = true;
		m_rect = _Rectangle(fX, fY, 40, 40);
		m_workingArea = _Rectangle(fX-SizeTile*6, fY-SizeTile*6, SizeTile*12, SizeTile*12);
		m_vX = 2;
		m_vY = 0;
		break;
	case UNIT_FIRE1:
		m_canCollide = true;
		m_checkedItem = true;
		m_canBeDestroyed = false;
		m_rect = _Rectangle(fX,fY, SizeTile, SizeTile*2);
		m_workingArea = _Rectangle(fX,fY,SizeTile,SizeTile*2);
		break;
	case UNIT_TRAP:
		m_canCollide = true;
		m_checkedItem = true;
		m_canBeDestroyed = false;
		m_rect = _Rectangle(fX,fY, SizeTile, SizeTile*2);
		m_workingArea = _Rectangle(fX,fY,SizeTile,SizeTile*2);
		break;
	case UNIT_GROUND1M2:
		m_canCollide = true;
		m_rect = _Rectangle(fX, fY, SizeTile*11, SizeTile);
		m_workingArea = _Rectangle(fX, fY, SizeTile*11, SizeTile);
		break;
	case UNIT_GRASS1M2:
		m_rect = _Rectangle(fX, fY, SizeTile*14, SizeTile*5);
		m_workingArea = _Rectangle(fX, fY, SizeTile*14, SizeTile*5);
		break;
	case UNIT_GRASS2M2:
		m_rect = _Rectangle(fX, fY, SizeTile*14, SizeTile*5);
		m_workingArea = _Rectangle(fX, fY, SizeTile*14, SizeTile*5);
		break;
	case UNIT_ROCKM2:
		m_canCollide = true;
		m_canBeDestroyed = false;
		m_checkedItem = false;
		m_rect = _Rectangle(fX, fY, SizeTile*1, SizeTile*1);
		m_workingArea = _Rectangle(fX, fY, SizeTile*1, SizeTile*1);
		break;
	case UNIT_CLOUD:
		m_canCollide = true;
		m_rect = _Rectangle(fX, fY, 60, 37);
		m_workingArea = _Rectangle(fX-SizeTile, fY-SizeTile, SizeTile*2, SizeTile*2);
		m_vX = 1;
		break;
	default:
		break;
	}
	m_health = 1;
	m_style = style;
	m_fx = fX;
	m_fy = fY;
	m_iHeight = (int)(m_rect.bottom  - m_rect.top);
	m_iWidth = (int)(m_rect.right - m_rect.left);
}
/************************************************************************/
/*                             Free                                     */
/************************************************************************/
void CCObject::Free()
{
	m_style = NULL;
}