#include "Rectangle.h"


CRectangle::CRectangle(void)
{
}


CRectangle::~CRectangle(void)
{
}

CRectangle::CRectangle(float fX, float fY, int width, int height)
{
	m_rect.top = (long)fY;
	m_rect.left = (long)fX;
	m_rect.bottom = (long)(fY + (float)height);
	m_rect.right = (long)(fX + (float)width);
}