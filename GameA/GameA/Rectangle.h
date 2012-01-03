#pragma once
#include <stdlib.h>
#include <Windows.h>
class CRectangle
{
	
public:
	/************************************************************************/
	/*                        Public variables                              */
	/************************************************************************/
	RECT m_rect;
	/************************************************************************/
	/*                    Constructors & Destructor                         */
	/************************************************************************/
	CRectangle(void);
	~CRectangle(void);
	CRectangle(float fX, float fY, int width, int height);
};

