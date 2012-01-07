#pragma once
#include "CObject.h"
#include "CObjectsList.h"
#include "Information.h"
#include "Collision.h"

#define MAXNODE 5

class QuadNode
{
public:
	/************************************************************************/
	/*                         Public variables                             */
	/************************************************************************/
	ListNodes* m_objectsList;
	RECT m_rect;
	int m_count;
	int m_level;
	QuadNode* m_topLeft;
	QuadNode* m_topRight;
	QuadNode* m_bottomLeft;
	QuadNode* m_bottomRight;
	/************************************************************************/
	/*                    Constructor & Destructor                          */
	/************************************************************************/
	QuadNode()
	{
		m_topLeft = m_topRight = m_bottomLeft = m_bottomRight = NULL;
		m_objectsList = new ListNodes();
		m_count = 0;
	}
	QuadNode(RECT rect)
	{
		m_topLeft = m_topRight = m_bottomLeft = m_bottomRight = NULL;
		m_objectsList = new ListNodes();
		m_count = 0;
		m_level = 0;
		m_rect = rect;
	}
	QuadNode(float fX, float fY, int width, int height)
	{
		m_rect.left = (long)fX;
		m_rect.top = (long)fY;
		m_rect.bottom = (long)(fY + height);
		m_rect.right = (long)(fX + width);
		m_bottomLeft = m_bottomRight = m_topLeft = m_topRight = NULL;
		m_objectsList = new ListNodes();
		m_count = 0;
		m_level = 0;
	}
	~QuadNode(void);
};



class CQuadTree
{
public:
	/************************************************************************/
	/*                         Public variables                             */
	/************************************************************************/
	
	QuadNode* m_root;
	float m_fX; // Begin
	float m_fY; // Begin

	/************************************************************************/
	/*                    Constructor & Destructor                          */
	/************************************************************************/
	CQuadTree(void);
	~CQuadTree(void);
	CQuadTree(int width, int height);
	/************************************************************************/
	/*							Methods                                     */
	/************************************************************************/
	void AddObject(QuadNode* node, CCObject* object);
	void AddObject(CCObject* object);
	void Free(QuadNode* node);
	void Free();
	void SetHealth(QuadNode* node);
	void SetHealth();
	void SetObjectsList(ListNodes* objectsList, RECT rect);
};

void AddObjectInRect(ListNodes	* objectsList,QuadNode* node, RECT rect);
bool CheckNodeCollideWithList(Node* node,ListNodes* objectsList);
bool CheckRectCollideWithList(RECT rect, ListNodes* objectsList);
bool CheckRectCollideWithList(RECT rect, ListNodes* objectsList, char style);
CCObject* ObjectCheckRectWithList(RECT rect, ListNodes* objectsList);
CCObject* ObjectCheckRectWithList(RECT rect, ListNodes* objectList, char style);
CCObject* ObjectCheckRectWithListCut(RECT rect, ListNodes* objectsList);
CCObject* ObjectCheckRectWithListCheckItems(RECT rect, ListNodes* objectsList);

