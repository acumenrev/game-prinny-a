#include "Collision.h"

#pragma region Constructor & Destructor
/************************************************************************/
/*                          Constructor					                */
/************************************************************************/
CCollision::CCollision(void)
{
}
/************************************************************************/
/*                          Destructor                                  */
/************************************************************************/
CCollision::~CCollision(void)
{
}

#pragma endregion 

#pragma region Methods
/************************************************************************/
/*        Check RECT a collides with RECT b                             */
/************************************************************************/
bool CCollision::CheckCollisionBetween2Rect(RECT a, RECT b)
{
	if(a.bottom < b.bottom &&
		a.left > b.left &&
		a.right < b.right &&
		a.top > b.top)
	{
		return false;
	}
	return true;
}
/************************************************************************/
/*        Check RECT a stays inside RECT b                              */
/************************************************************************/
bool CCollision::CheckStayInAnotherRect(RECT a, RECT b)
{
	if(a.bottom <= b.bottom &&
		a.left >= b.left &&
		a.right <= b.right &&
		a.top >= b.top)
	{
		return true;
	}
	return false;
}
#pragma endregion 
