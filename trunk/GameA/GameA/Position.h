#pragma once
class CPosition
{
public:
	// variables
	float m_fX, m_fY;

	// constructors & destructor
	CPosition(void);
	~CPosition(void);
	CPosition(float fX, float fY);

	// overloading operator + and -
	CPosition operator +(CPosition p);
	CPosition operator -(CPosition p);
};

