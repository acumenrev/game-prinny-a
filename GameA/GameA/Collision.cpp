#include "Collision.h"



#pragma region Methods
/************************************************************************/
/*        Check RECT a collides with RECT b                             */
/************************************************************************/
bool CheckCollisionBetween2Rect(RECT a, RECT b)
{
	if (a.bottom<b.top
		||a.top>b.bottom
		||a.right<b.left
		||a.left>b.right)
	{
		return false;
	}
	return true;
}
/************************************************************************/
/*        Check RECT a stays inside RECT b                              */
/************************************************************************/
bool CheckStayInAnotherRect(RECT a, RECT b)
{
	if(a.bottom < b.bottom &&
		a.left > b.left &&
		a.right < b.right &&
		a.top > b.top)
	{
		return true;
	}
	return false;
}
/************************************************************************/
/*                          RECTANGLE                                   */
/************************************************************************/
RECT _Rectangle(float fX, float fY, int width, int height)
{
	RECT r;
	r.top = (long)fY;
	r.left = (long)fX;
	r.bottom = (long)fY + (long)height -1;
	r.right = (long)fX + (long)width -1;
	return r;
}
#pragma endregion 
