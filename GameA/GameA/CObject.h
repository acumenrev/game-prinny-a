#pragma once
#include "Position.h"
class CCObject
{
public:
	// variables
	CPosition m_pos;
	int m_iWidth;
	int m_iHeight;
	// Constructors & Destructor
	CCObject(void);
	~CCObject(void);
	CCObject(float fX, float fY, float Width, float Height);
};

