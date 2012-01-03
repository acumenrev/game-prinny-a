#pragma once
#include <Windows.h>
#include <stdlib.h>
class CCollision
{
public:
	CCollision(void);
	~CCollision(void);
	RECT _Rectangle(float fX, float fY, int width, int height);
	bool CheckCollisionBetween2Rect(RECT a, RECT b);
	bool CheckStayInAnotherRect(RECT a, RECT b);
};

