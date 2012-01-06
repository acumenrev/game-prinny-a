#include "Camera.h"

#pragma region Constructors & Destructor

/************************************************************************/
/*                           Constructor			                    */
/************************************************************************/
CCamera::CCamera(void)
{
	m_fX = 0;
	m_fY = 0;
	m_vX = 50;
	m_vY = 10;
}
//////////////////////////////////////////////////////////////////////////
CCamera::CCamera(long vX,long vY)
{
	m_fX = 0;
	m_fY = 0;
	m_vX = vX;
	m_vY = vY;
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

void CCamera::SetViewPort(long fX, long fY,long width, long height)
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
	if(Abs(fX - m_fX) > 0.3)
	{
		m_fX += (fX-m_fX)/m_vX;
	}
	else
		m_fX = fX;
	if(Abs(fY - m_fY) > 0.3)
	{
		m_fY += (fY-m_fY)/m_vY;
	}
	else
		m_fY = fY;
}

#pragma endregion 