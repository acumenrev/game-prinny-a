#include "Information.h"
#include "Sprite.h"
#include "Position.h"
#include "Camera.h"
#include "CObjectsList.h"
#include "Collision.h"
#include "QuadTree.h"
#define GiatocX 0.5
#define GiatocY 0.5
#define VxMax 3
#define VJump 10
#define Masat 0.9

enum State_Prinny
{
	Move_Right = 5,
	Move_Left = 4,
	Stop_Right = 11,
	Stop_Left = 10,
	Stand_Right = 7,
	Stand_Left = 6,
	Jump_Up_Right = 2,
	Jump_Up_Left = 0,
	Jump_Down_Right = 3,
	Jump_Down_Left = 1,
	Shoot_Right = 9,
	Shoot_Left = 8
};
enum State_Prinny_2
{
	Stand = 0,
	Jump,
	Shoot
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

	int m_heal;
	CCamera * m_camera;
	ListNodes * m_listObject;
	CQuadTree * m_quadtree;
	
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
		m_listObject = new ListNodes();
		m_quadtree = new CQuadTree();
		InitSprite();
		m_heal = 1;
	}

	RECT m_rectSprite;
	bool IsRight;
	int m_spriteIndex_X;
	int m_spriteIndex_Y;
	int m_srpiteIndexStar_X;
	int m_max_spriteIndex_X[20];
	long m_spriteDelay;
	long m_spriteDelay_max;
	int m_statePrinny;
	void InitSprite()
	{
		m_max_spriteIndex_X[Move_Left] = 6;
		m_max_spriteIndex_X[Move_Right] = 6;
		m_max_spriteIndex_X[Stop_Left] = 2;
		m_max_spriteIndex_X[Stop_Right] = 2;
		m_max_spriteIndex_X[Stand_Right] = 1;
		m_max_spriteIndex_X[Stand_Left] = 1;
		m_max_spriteIndex_X[Jump_Down_Left] = 4;
		m_max_spriteIndex_X[Jump_Down_Right] = 4;
		m_max_spriteIndex_X[Jump_Up_Left] = 2;
		m_max_spriteIndex_X[Jump_Up_Right] = 2;
		m_max_spriteIndex_X[Shoot_Right] = 7;
		m_max_spriteIndex_X[Shoot_Left] = 7;

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
			m_spriteDelay_max =10;
			UpdateSpiteStand(keys);
			break;
		case Jump:
			m_spriteDelay_max = 15;
			UpdateSpriteJump(keys);
			break;
		case Shoot:
			m_spriteDelay_max = 3;
			UpdateSpriteShoot(keys);
			break;
		}

		m_spriteDelay++;
		if(m_spriteDelay >= m_spriteDelay_max)
		{
			m_rectSprite = _Rectangle((float)(m_spriteIndex_X*56),(float)(m_spriteIndex_Y*56),56,56);
			m_spriteIndex_X++;
			if(m_spriteIndex_X >= m_max_spriteIndex_X[m_spriteIndex_Y])
			{
				m_spriteIndex_X = m_srpiteIndexStar_X;
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
				m_spriteIndex_X = 7;
				m_srpiteIndexStar_X = 7;
				m_spriteDelay_max = 20;
			}
			if (IsRight == false && m_spriteIndex_Y != Stand_Left)
			{
				m_spriteIndex_Y = Stand_Left;
				m_spriteIndex_X = 7;
				m_srpiteIndexStar_X = 7;
				m_spriteDelay_max = 25;
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
					m_srpiteIndexStar_X = 0;
				}
			}
			else
			{
				if (m_spriteIndex_Y != Stop_Right && KEYUP(keys,DIK_RIGHT))
				{
					m_spriteIndex_Y = Stop_Right;
					m_spriteIndex_X = 0;
					m_srpiteIndexStar_X = 0;
					m_spriteDelay_max = 20;
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
					m_srpiteIndexStar_X = 0;
				}
			}
			else
			{
				if (m_spriteIndex_Y != Stop_Left && KEYUP(keys,DIK_LEFT))
				{
					m_spriteIndex_Y = Stop_Left;
					m_spriteIndex_X = 0;
					m_srpiteIndexStar_X = 0;
					m_spriteDelay_max = 20;
				}
			}
		}
	}
	void UpdateSpriteJump(char keys[256])
	{
		if(IsRight == true)
		{
			if (m_vY < 0)
			{
				if(m_spriteIndex_Y != Jump_Up_Right)
				{
					m_spriteIndex_Y = Jump_Up_Right;
					m_spriteIndex_X = 0;
					m_srpiteIndexStar_X = 0;
				}
			} 
			else
			{
				if(m_spriteIndex_Y != Jump_Down_Right)
				{
					m_spriteIndex_Y = Jump_Down_Right;
					m_spriteIndex_X = 0;
					m_srpiteIndexStar_X = 0;
				}
			}
		}
		else
		{
			if (m_vY < 0)
			{
				if(m_spriteIndex_Y != Jump_Up_Left)
				{
					m_spriteIndex_Y = Jump_Up_Left;
					m_spriteIndex_X = 0;
					m_srpiteIndexStar_X = 0;
				}
			} 
			else
			{
				if(m_spriteIndex_Y != Jump_Down_Left)
				{
					m_spriteIndex_Y = Jump_Down_Left;
					m_spriteIndex_X = 0;
					m_srpiteIndexStar_X = 0;
				}
			}
		}
	}
	void UpdateSpriteShoot(char keys[256])
	{
		if(IsRight == true)
		{
			if(m_spriteIndex_Y != Shoot_Right)
			{
				m_spriteIndex_Y = Shoot_Right;
				m_spriteIndex_X = 0;
				m_srpiteIndexStar_X = 0;
			}
		}
		else
		{
			if (m_spriteIndex_Y != Shoot_Left)
			{
				m_spriteIndex_Y = Shoot_Left;
				m_spriteIndex_X = 0;
				m_srpiteIndexStar_X = 0;
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
	// Jump
	void jump()
	{
		IsJump = true;
		m_statePrinny = Jump;
			m_vY = -VJump;		
			y += m_vY;
			IsJump = false;
		m_statePrinny = Stand;
		
	}
	// shoot
	void PrinnyShoot(char keys[256])
	{

		if (KEYDOWN(keys,DIK_SPACE))
		{
			m_statePrinny = Shoot;
		}
		else
		{
			m_statePrinny = Stand;
		}
	}
	// update
	int Update(char keys[256],char last_keys[256],CQuadTree * _m_quadtree)
	{
		if (KEYDOWN(keys,DIK_ESCAPE) && KEYUP(last_keys,DIK_ESCAPE))
		{
			return 3;
		}
		if (m_heal == 0)
		{
			return 2;
		}

		Move(keys);
		PrinnyShoot(keys);
		//
		//m_listObject->Free();
		//m_quadtree->SetObjectsList(m_listObject,_Rectangle(x,y,m_wight,m_height));
		//
		/*if(CheckRectCollideWithList(_Rectangle((x+m_vX),(y+m_vY),m_wight,m_height),m_listObject))
		{

		}*/

		UpdateSprite(keys);
		x += m_vX;

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