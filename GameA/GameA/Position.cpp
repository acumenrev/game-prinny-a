#include "Position.h"

#pragma region Constructors & Destructor

/************************************************************************/
/*                          Constructor                                 */
/************************************************************************/
CPosition::CPosition(void)
{
	this->m_fX = 0;
	this->m_fY = 0;
}
/************************************************************************/
/*                          Destructor                                  */
/************************************************************************/
CPosition::~CPosition(void)
{
}
/************************************************************************/
/*                          Constructor                                 */
/************************************************************************/
CPosition::CPosition(float fX, float fY)
{
	m_fY = fY;
	m_fX = fX;
}

#pragma endregion 

#pragma region Methods

/************************************************************************/
/*                         Override operator +                          */
/************************************************************************/
CPosition CPosition::operator+(CPosition p)
{
	CPosition r;
	r.m_fX = this->m_fX + p.m_fX;
	r.m_fY = this->m_fY + p.m_fY;
	return r;
}
/************************************************************************/
/*                         Override operator -                          */
/************************************************************************/
CPosition CPosition::operator-(CPosition p)
{
	CPosition r;
	r.m_fX = this->m_fX - p.m_fX;
	r.m_fY = this->m_fY - p.m_fY;
	return r;
}

#pragma endregion 