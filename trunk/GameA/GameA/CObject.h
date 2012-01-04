#pragma once
#include "Position.h"
#include "Information.h"
#include "Collision.h"
class CCObject
{
public:
	/************************************************************************/
	/*                         Public variables                             */
	/************************************************************************/
	CPosition m_pos;
	int m_iWidth;
	int m_iHeight;
	// Constructors & Destructor
	char m_style;
	RECT m_workingArea;
	float m_vX;
	float m_vY;
	float m_rotate;
	bool m_canCollide;
	bool m_canBeDestroyed;
	int m_spriteIndex;
	bool m_checkedItem;
	int m_scale;
	int m_health;
	RECT m_rect;
	/************************************************************************/
	/*                    Constructor & Destructor                          */
	/************************************************************************/
	CCObject(void);
	~CCObject(void);
	CCObject(float fX, float fY, char style);
	/************************************************************************/
	/*							Methods                                     */
	/************************************************************************/
	void Free();
};

