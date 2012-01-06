#include "Information.h"
#include "Sprite.h"
#include "Position.h"
#include "Camera.h"
#include "CObjectsList.h"
#include "Collision.h"
#include "QuadTree.h"
#include "Bass_Sound.h"
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
	/************************************************************************/
	/*                         Variables                                    */
	/************************************************************************/
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
	WaZ_Game_App::Bass_Sound* m_bassSound;
	int m_id;
	//////////////////////////////////////////////////////////////////////////
	// Sprite
	//////////////////////////////////////////////////////////////////////////
	RECT m_rectSprite;
	bool IsRight;
	int m_spriteIndex_X;
	int m_spriteIndex_Y;
	int m_srpiteIndexStar_X;
	int m_max_spriteIndex_X[20];
	long m_spriteDelay;
	long m_spriteDelay_max;
	int m_statePrinny;
	/************************************************************************/
	/*                             Methods                                  */
	/************************************************************************/
	CPrinny(float _x , float _y , float _m_height , float _m_wight , AllSprite * _m_allSprites , CCamera * _m_camera, WaZ_Game_App::Bass_Sound* bassSound)
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
		//UpdateSpriteShoot();
		m_heal = 1;
		//m_soundPlayer = _m_soundPlayer;	
		m_bassSound = bassSound;
	}
	/************************************************************************/
	/*                            Init Sprite                               */
	/************************************************************************/
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

		x_shoot = 0;
		delayShoot = 0;
		m_spriteIndex_X = 0;
		m_spriteIndex_Y = 0;
		m_spriteDelay = 0;
		IsRight = true;
		m_statePrinny = Stand;
	}
	/************************************************************************/
	/*                            Update Sprite                             */
	/************************************************************************/
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
		/*case Shoot:
			UpdateSpriteShoot();
			break;*/
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
	/************************************************************************/
	/*                      Update Sprite Stand			                    */
	/************************************************************************/
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
	/************************************************************************/
	/*                       Update sprite jump                             */
	/************************************************************************/
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
	/************************************************************************/
	/*                        Update sprite shoot                           */
	/************************************************************************/
	/*void UpdateSpriteShoot()
	{
		if(IsRight == true)
		{
			if(y_shoot != Shoot_Right)
			{
				y_shoot = Shoot_Right;
				x_shoot = 0;
				delayShoot = 7;
			}
		}
		else
		{
			if (y_shoot != Shoot_Left)
			{
				y_shoot = Shoot_Left;
				x_shoot = 0;
				delayShoot = 7;
			}
		}
	}*/
	/************************************************************************/
	/*                            Move                                          */
	/************************************************************************/
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
	/************************************************************************/
	/*                             Move Right                               */
	/************************************************************************/
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
	/************************************************************************/
	/*                           Jump                                       */
	/************************************************************************/
	void jump()
	{
		IsJump = true;
		m_statePrinny = Jump;
			m_vY = -VJump;		
			y += m_vY;
			IsJump = false;
		m_statePrinny = Stand;
		
	}
	/************************************************************************/
	/*                              Shoot                                   */
	/************************************************************************/
	int x_shoot;
	int y_shoot;
	int delayShoot;
	RECT m_rectSpritechem;
	void PrinnyShoot(char keys[256],char last_keys[256])
	{		
		if (IsRight == true)
		{
			y_shoot = 9;
		}
		else
		{
			y_shoot = 8;
		}
		if(x_shoot < m_max_spriteIndex_X[y_shoot])
		{
			delayShoot++;
			m_rectSpritechem = _Rectangle((float)(x_shoot*56),(float)(y_shoot*56),56,56);			
			if(delayShoot >= 3)
			{
				x_shoot++;
				delayShoot = 0;
			}	
		}
		else
		{
			if (KEYDOWN(keys,DIK_SPACE) && KEYUP(last_keys,DIK_SPACE))
			{
				m_bassSound->Play("Cut",true);
				x_shoot = 0;
				delayShoot = 0;
			}
			else
			{
				m_statePrinny = Stand;
			}		
		}
	}
	/************************************************************************/
	/*                                Update                                */
	/************************************************************************/
	int Update(char keys[256],char last_keys[256],CQuadTree * _m_quadtree)
	{
		if (KEYDOWN(keys,DIK_BACK) && KEYUP(last_keys,DIK_BACK))
		{
			return 3;
		}
		if (m_heal == 0)
		{
			return 2;
		}
		Move(keys);
		PrinnyShoot(keys,last_keys);
		//
		//m_listObject->Free();
		//m_quadtree->SetObjectsList(m_listObject,_Rectangle(x,y,m_wight,m_height));
		//
		/*if(CheckRectCollideWithList(_Rectangle((x+m_vX),(y+m_vY),m_wight,m_height),m_listObject))
		{
			IsJump = true;
			if (!CheckRectCollideWithList(_Rectangle(x,y+m_vY,m_wight,m_height),m_listObject)) // va cham trai' phai?
			{
				if (KEYDOWN(keys,DIK_UP) && KEYUP(last_keys,DIK_UP))
				{
					jump();
				}
			}
			else
			{
				if (!CheckRectCollideWithList(_Rectangle(x+m_vX,y,m_wight,m_height),m_listObject)) // va cham tren duoi'
				{
					if(m_vY > 0) // va cham tren
					{
						if(KEYDOWN(keys,DIK_UP) && KEYUP(last_keys,DIK_UP))
						{
							m_vY = -VJump;
							m_statePrinny = Jump;
						}
						else
						{
							m_vY = 0;
							m_statePrinny = Stand;
						}
					}
					else  // va cham duoi
					{
						m_vY = 0;
						IsJump = false;
					}
				}
				else
				{
					if(KEYDOWN(keys,DIK_UP) && KEYUP(last_keys,DIK_UP))
					{
						jump();
					}
					else
					{
						m_vX = 0;
						m_vY = 0;
					}
				}
			}
		}
		else
		{
			m_statePrinny = Jump;
			if(KEYDOWN(keys,DIK_UP) && KEYUP(last_keys,DIK_UP) && IsJump == true)
			{
				m_vY = -VJump;
				IsJump = false;
			}
		}
		///////////////////////
		
		/////////////////
		if(!CheckRectCollideWithList(_Rectangle((x+m_vX),(y+m_vY),m_wight,m_height),m_listObject))
		{
			if(CheckCollisionBetween2Rect(_Rectangle((x+m_vX),(y+m_vY),m_wight,m_height),m_quadtree->m_root->m_rect))
			{
				y += m_vY;
				x += m_vX;
			}
			else
			{
				if (!CheckCollisionBetween2Rect(_Rectangle((x+m_vX),y,m_wight,m_height),m_quadtree->m_root->m_rect))
				{
					m_vX = 0;
				}
				if (!CheckCollisionBetween2Rect(_Rectangle(x,y+m_vY,m_wight,m_height),m_quadtree->m_root->m_rect))
				{
					m_vY = 0;
				}
				y += m_vY;
				x += m_vX;
			}
		}
		else
		{
			if(CheckRectCollideWithList(_Rectangle(x,y,m_wight,m_height),m_listObject))
			{

			}
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
		if(x>200 && x<250)
		{
			m_heal = 0;
		}
		return 0;
	}
};
