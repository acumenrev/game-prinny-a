#include "Information.h"
#include "Sprite.h"
#include "Position.h"
#include "Camera.h"
#include "CObjectsList.h"
#include "Collision.h"
#include "QuadTree.h"
#include "Bass_Sound.h"
#include "CObject.h"
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
	float x_save;
	float y_save;
	float m_height;
	float m_wight;

	float m_vX;
	float m_vY;

	bool IsJump;

	int m_heal;
	CCamera * m_camera;
	ListNodes * m_listObject;
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
		x_save = _x;
		y_save = _y;
		x_before = _x;
		y_before = _y;
		m_height = _m_height;
		m_wight = _m_wight;

		m_vX = 0;
		m_vY = 0;

		IsJump = false;
		
		m_camera = _m_camera;
		m_listObject = new ListNodes();
		InitSprite();
		m_heal = 1;	
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

		x_prinnyCut = 0;
		x_kiem = 0;
		DelayCut = 0;
		m_spriteIndex_X = 0;
		m_spriteIndex_Y = 0;
		m_spriteDelay = 0;
		IsRight = true;
		m_statePrinny = Jump;
	}
	/************************************************************************/
	/*                            Update Sprite                             */
	/************************************************************************/
	void UpdateSprite(char keys[256])
	{
		switch(m_statePrinny)
		{
		case Stand:
			m_spriteDelay_max =8;
			UpdateSpiteStand(keys);
			break;
		case Jump:
			m_spriteDelay_max = 10;
			UpdateSpriteJump(keys);
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
				m_spriteDelay_max = 8;
			}
			if (IsRight == false && m_spriteIndex_Y != Stand_Left)
			{
				m_spriteIndex_Y = Stand_Left;
				m_spriteIndex_X = 7;
				m_srpiteIndexStar_X = 7;
				m_spriteDelay_max = 8;
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
		bool CollisionLeft = CheckRectCollideWithList(_Rectangle(x-VJump,y-VJump,m_wight,m_height),m_listObject);
		bool CollisionRight = CheckRectCollideWithList(_Rectangle(x+VJump,y-VJump,m_wight,m_height),m_listObject);

		if(CollisionLeft == true && CollisionRight == false)
		{
			m_vX = VJump*0.2;
		}
		if(CollisionLeft == false && CollisionRight == true)
		{
			m_vX = -VJump*0.2;
		}
		m_vY = -VJump;
		m_statePrinny = Jump;
	}
	/************************************************************************/
	/*                              Shoot                                   */
	/************************************************************************/
	int x_prinnyCut;
	int y_prinnyCut;
	int x_kiem;
	int y_kiem;
	int DelayCut;
	int TiLeRenderX;
	int TiLeRenderY;
	RECT m_rectSpritechem;
	RECT m_rectSpritekiem;
	void PrinnyCut(char keys[256],char last_keys[256],CQuadTree* m_quadTree)
	{		
		if (IsRight == true)
		{
			y_prinnyCut = 9;
			y_kiem = 1;
			TiLeRenderX = -25;
			TiLeRenderY = -5;
		}
		else
		{
			y_prinnyCut = 8;
			y_kiem = 0;
			TiLeRenderX = -40;
			TiLeRenderY = -5;
		}
		if(x_prinnyCut < m_max_spriteIndex_X[y_prinnyCut])
		{
			DelayCut++;
			m_rectSpritechem = _Rectangle((float)(x_prinnyCut*56),(float)(y_prinnyCut*56),56,56);	
			m_rectSpritekiem = _Rectangle((float)(x_kiem*108),(float)(y_kiem*64),108,64);
			if(DelayCut >= 5)
			{
				x_kiem++;
				x_prinnyCut++;
				DelayCut = 0;
				m_listObject->ResetListObject();
				m_quadTree->SetObjectsList(m_listObject,_Rectangle(x + TiLeRenderX ,y + TiLeRenderY ,108,64));
				int Cutting = 0;
				do 
				{
					Cutting = 0;
					CCObject * ob_check = ObjectCheckRectWithListCut(_Rectangle(x + TiLeRenderX ,y + TiLeRenderY ,108,64),m_listObject);
					if(ob_check)
					{
						switch(ob_check->m_style)
						{
						case UNIT_ROCK1:
							ob_check->m_health = 0;
							Cutting = 1;
							break;
						}
					}
				} while (Cutting == 1);
			}	
		}
		else
		{
			if (KEYDOWN(keys,DIK_SPACE) && KEYUP(last_keys,DIK_SPACE))
			{
				m_bassSound->Play("Cut",true);
				x_prinnyCut = 0;
				x_kiem = 0;
				DelayCut = 0;
				
			}	
		}
	}
	/************************************************************************/
	/*                                Update                                */
	/************************************************************************/
	float x_before;
	float y_before;
	int Update(char keys[256],char last_keys[256],CQuadTree * m_quadTree)
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
		PrinnyCut(keys,last_keys,m_quadTree);
		
		m_listObject->ResetListObject();
		m_quadTree->SetObjectsList(m_listObject,_Rectangle(x,y,m_wight,m_height));
		//
		if(CheckRectCollideWithList(_Rectangle((x+m_vX),(y+m_vY),m_wight,m_height),m_listObject))
		{ 
			IsJump = true;
			if (!CheckRectCollideWithList(_Rectangle(x,y+m_vY,m_wight,m_height),m_listObject)) // va cham trai' phai?
			{			
				if (KEYDOWN(keys,DIK_UP) && KEYUP(last_keys,DIK_UP))
				{	
					jump();				
				}
				else
				{
						m_vX = 0;
						m_vY = VJump*0.3;	
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
		if (m_vX < GiatocX && m_vX > -GiatocX)
		{
			m_vX = 0;
		}
		if (m_vY < GiatocY && m_vY > -GiatocY)
		{
			m_vY = 0;
		}
		if(y+m_height+10 > 600)
		{
			m_heal = 0;
		}
		/////////////////
		if(!CheckRectCollideWithList(_Rectangle((x+m_vX),(y+m_vY),m_wight,m_height),m_listObject))
		{
			if(CheckStayInAnotherRect(_Rectangle((x+m_vX),(y+m_vY),m_wight,m_height),m_quadTree->m_root->m_rect))
			{
				x_before = x;
				y_before = y;
				y += m_vY;
				x += m_vX;
			}
			else
			{
				if (!CheckStayInAnotherRect(_Rectangle((x+m_vX),y,m_wight,m_height),m_quadTree->m_root->m_rect))
				{
					m_vX = 0;
				}
				if (!CheckStayInAnotherRect(_Rectangle(x,y+m_vY,m_wight,m_height),m_quadTree->m_root->m_rect))
				{
					m_vY = 0;
				}
				y += m_vY;
				x += m_vX;
			}
		}
		else
		{
			if(CheckRectCollideWithList(_Rectangle(x_before,y_before,m_wight,m_height),m_listObject))
			{
				m_heal = 0;
			}
			else
			{
				x = x_before;
				y = y_before;
				m_vX = 0;
				m_vY = 0;
			}
		}
		UpdateSprite(keys);
		/////////////////
		CCObject * ob_check = ObjectCheckRectWithListCheckItems(_Rectangle(x,y,m_wight,m_height),m_listObject);
		if(ob_check)
		{
			switch(ob_check->m_style)
			{
			case UNIT_ROCK1:
				m_heal = 0;
				break;
			}
		}
		return 0;
	}
	void ReSpam(CQuadTree * m_quadTree)
	{
		m_heal = 1;
		x = x_save;
		y = y_save;
		m_vX = 0;
		m_vY = 0;
		m_quadTree->SetHealth();
	}
};
