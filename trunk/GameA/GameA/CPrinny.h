#include "Information.h"
#include "Sprite.h"
#include "Position.h"
#include "Camera.h"
#include "CObjectsList.h"
#define GiatocX 0.5
#define GiatocY 0.5
#define VxMax 6
#define VJump 10
#define Masat 0.9

enum State_Prinny
{
	Move_Right = 5,
	Move_Left = 4,
	Stop_Right = 5,
	Stop_Left = 4,
	Stand_Right = 7,
	Stand_Left = 6,
	Jump_Up_Right,
	Jump_Up_Left,
	Jump_Down_Right,
	Jump_Down_Left
};
enum State_Prinny_2
{
	Stand = 0,
	Jump
};

class CPrinny
{
public:
	AllSprite * m_allSprites;

	float x;
	float y;
	float m_height;
	float m_wight;

	float m_vX;
	float m_vY;

	bool IsJump;

	CCamera * m_camera;
	ListNodes * m_listObject;
	
	CPrinny(float _x , float _y , float _m_height , float _m_wight , AllSprite * _m_allSprites , CCamera * _m_camera)
	{
		m_allSprites = _m_allSprites;

		x = _x;
		y = _y;
		m_height = _m_height;
		m_wight = _m_wight;

		m_vX = 0;
		m_vY = 0;

		IsJump = false;
		
		m_camera = _m_camera;

		InitSprite();
	}

	RECT m_rectSprite;
	bool IsRight;
	int m_spriteIndex_X;
	int m_spriteIndex_Y;
	int m_max_spriteIndex_X[20];
	long m_spriteDelay;
	long m_spriteDelay_max;
	int m_statePrinny;
	void InitSprite()
	{
		m_max_spriteIndex_X[Move_Left] = 6;
		m_max_spriteIndex_X[Move_Right] = 6;
		m_max_spriteIndex_X[Stop_Left] = 1;
		m_max_spriteIndex_X[Stop_Right] = 1;
		m_max_spriteIndex_X[Stand_Right] = 9;
		m_max_spriteIndex_X[Stand_Left] = 9;
		m_max_spriteIndex_X[Jump_Down_Left] = 6;
		m_max_spriteIndex_X[Jump_Down_Right] = 6;
		m_max_spriteIndex_X[Jump_Up_Left] = 6;
		m_max_spriteIndex_X[Jump_Up_Right] = 6;

		m_spriteIndex_X = 0;
		m_spriteIndex_Y = 0;
		m_spriteDelay = 0;
		IsRight = true;
		m_statePrinny = Stand;
	}
	void UpdateSprite(char keys[256])
	{
		switch(m_statePrinny)
		{
		case Stand:
			m_spriteDelay_max = 7;
			UpdateSpiteStand(keys);
			break;
		case Jump:
			break;
		}

		m_spriteDelay++;
		if(m_spriteDelay >= m_spriteDelay_max)
		{
			m_rectSprite = _Rectangle((float)(m_spriteIndex_X*56),(float)(m_spriteIndex_Y*56),56,56);
			m_spriteIndex_X++;
			if(m_spriteIndex_X >= m_max_spriteIndex_X[m_spriteIndex_Y])
			{
				m_spriteIndex_X = 0;
			}
			m_spriteDelay = 0;
		}
	}

	void UpdateSpiteStand(char keys[256])
	{
		if (m_vX == 0)
		{
			if(IsRight == true && m_spriteIndex_Y != Stand_Right)
			{
				m_spriteIndex_Y = Stand_Right;
				m_spriteIndex_X = 0;
			}
			if (IsRight ==false && m_spriteIndex_Y != Stand_Left)
			{
				m_spriteIndex_Y = Stand_Left;
				m_spriteIndex_X = 0;
			}
		}
		if(m_vX >0)
		{
			if (IsRight == true || (KEYDOWN(keys,DIK_LEFT) && KEYDOWN(keys,DIK_RIGHT)))
			{
				if (m_spriteIndex_Y != Move_Right)
				{
					m_spriteIndex_Y = Move_Right;
					m_spriteIndex_X = 0;
				}
			}
			else
			{
				if (m_spriteIndex_Y != Stop_Right && KEYUP(keys,DIK_RIGHT))
				{
					m_spriteIndex_Y = Stop_Right;
					m_spriteIndex_X = 0;
				}
			}
		}
		if(m_vX <0)
		{
			if (IsRight == false || (KEYDOWN(keys,DIK_LEFT) && KEYDOWN(keys,DIK_RIGHT)))
			{
				if (m_spriteIndex_Y != Move_Left)
				{
					m_spriteIndex_Y = Move_Left;
					m_spriteIndex_X = 0;
				}
			}
			else
			{
				if (m_spriteIndex_Y != Stop_Left && KEYUP(keys,DIK_LEFT))
				{
					m_spriteIndex_Y = Stop_Left;
					m_spriteIndex_X = 0;
				}
			}
		}
	}
	//  move
	void Move(char keys[256])
	{
		m_vY += GiatocX;
		bool IsMasat = true;
		if(KEYDOWN(keys,DIK_RIGHT))
		{
			MoveRight();
			IsMasat = false;
			IsRight = true;
		}
		if(KEYDOWN(keys,DIK_LEFT))
		{
			MoveLeft();
			IsMasat = false;
			IsRight = false;
		}
		if (IsMasat == true)
		{
			m_vX = m_vX*(float)Masat;
		}
	}
	void MoveRight()
	{
		if(m_vX < VxMax)
		{
			m_vX += GiatocX;
		}
		else
			m_vX = VxMax;
	}
	void MoveLeft()
	{
		if(m_vX > -VxMax)
		{
			m_vX -= GiatocX;
		}
		else
			m_vX = -VxMax;
	}
	// update
	int Update(char keys[256],char last_keys[256])
	{
		Move(keys);
		UpdateSprite(keys);
		if (m_vX < GiatocX && m_vX > -GiatocX)
		{
			m_vX = 0;
		}
		if (m_vY < GiatocY && m_vY > -GiatocY)
		{
			m_vY = 0;
		}
		return 0;
	}
};
