#include "Camera.h"

#pragma region Constructors & Destructor

/************************************************************************/
/*                           Constructor			                    */
/************************************************************************/
CCamera::CCamera(void)
{
	m_fX = 0;
	m_fY = 0;
}
/************************************************************************/
/*                           Destructor					                */
/************************************************************************/
CCamera::~CCamera(void)
{
}
/************************************************************************/
/*                           ABS                                        */
/************************************************************************/
float CCamera::Abs(float a)
{
	if(a >= 0)
	{
		return a;
	}
	else
	{
		return -a;
	}
}

#pragma endregion 

#pragma region Methods

void CCamera::SetViewPort(float fX, float fY,int width, int height)
{

	if(fX < 0)
	{
		fX = 0;
	}
	if(fX > width - WINDOW_WIDTH)
	{
		fX = (float)width - WINDOW_WIDTH;
	}
	if(fY < 0)
	{
		fY = 0;
	}
	if(fY > height - WINDOW_HEIGHT)
	{
		fY = (float)height - WINDOW_HEIGHT;
	}
	m_fX += fX - width;
	m_fY += fY - height;
}

#pragma endregion 