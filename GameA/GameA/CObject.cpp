#include "CObject.h"

/************************************************************************/
/*                           Constructor                                */
/************************************************************************/
CCObject::CCObject(void)
{
	m_pos.m_fX = 0;
	m_pos.m_fY = 0;
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
	m_pos.m_fX = fX;
	m_pos.m_fY = fY;
	m_rotate = 0;
	m_scale = 1;
	m_vX = 0;
	m_vY = 0;
	m_workingArea = _Rectangle(fX,fY,SizeTile,SizeTile);
	m_canCollide = false;
	m_canBeDestroyed = false;
	m_checkedItem = false;
	m_spriteIndex = 0;
	m_style = style;
}
/************************************************************************/
/*                             Free                                     */
/************************************************************************/
void CCObject::Free()
{
	m_style = NULL;
}