#include "QuadTree.h"

#pragma region Constructors & Destructor

/************************************************************************/
/*                              Constructor                             */
/************************************************************************/
CQuadTree::CQuadTree(void)
{
}
/************************************************************************/
/*                              Destructor                              */
/************************************************************************/
CQuadTree::~CQuadTree(void)
{
}

#pragma endregion 

#pragma region Methods
/************************************************************************/
/*                                                                      */
/************************************************************************/
void CQuadTree::AddObject(QuadNode* root, CCObject* object)
{
	if(m_root != NULL)
	{
		m_root->m_count++;
		long topBottom = (m_root->m_rect.top + m_root->m_rect.bottom)/2;
		long leftRight = (m_root->m_rect.left + m_root->m_rect.right)/2;
		RECT temp;
		// Check in Top Left
		temp.top = m_root->m_rect.top;
		temp.bottom = topBottom;
		temp.left = m_root->m_rect.left;
		temp.right = leftRight;
		// Check TEMP rect stays in another rect
		// do something
		/*if (checkRec_in_Rec(obj->VungHoatDong,Rec_Tam)&&Root->level<SoNodeToiDa)
		{
		if (!Root->LT)
		Root->LT=new QuadNode(Rec_Tam);
		Root->LT->level=Root->level+1;
		return AddObject(Root->LT,obj);
		}*/
		// Check in Bottom Left
		temp.top = topBottom;
		temp.bottom = m_root->m_rect.bottom;
		temp.left = m_root->m_rect.left;
		temp.right = leftRight;
		// Check TEMP rect stays in another rect
		/*if (checkRec_in_Rec(obj->VungHoatDong,Rec_Tam)&&Root->level<SoNodeToiDa)
		{
			if (!Root->LB)
				Root->LB=new QuadNode(Rec_Tam);
			Root->LB->level=Root->level+1;
			return AddObject(Root->LB,obj);
		}*/
		// Check in Right top
		temp.top = m_root->m_rect.top;
		temp.bottom = topBottom;
		temp.left = leftRight;
		temp.right = m_root->m_rect.right;
		// Check TEMP rect stays in another rect
		/*if (checkRec_in_Rec(obj->VungHoatDong,Rec_Tam)&&Root->level<SoNodeToiDa)
		{
			if (!Root->RT)
				Root->RT=new QuadNode(Rec_Tam);
			Root->RT->level=Root->level+1;
			return AddObject(Root->RT,obj);
		}*/
		// Check in Bottom Right
		temp.top = topBottom;
		temp.bottom = m_root->m_rect.bottom;
		temp.left = leftRight;
		temp.right = m_root->m_rect.right;
		// Check TEMP rect stays in another rect
		/*if (checkRec_in_Rec(obj->VungHoatDong,Rec_Tam)&&Root->level<SoNodeToiDa)
		{
			if (!Root->RB)
				Root->RB=new QuadNode(Rec_Tam);
			Root->RB->level=Root->level+1;
			return AddObject(Root->RB,obj);
		}*/
		// Assign object
		m_root->m_objectsList->AddNode(object);
	}
}
/************************************************************************/
/*               Add an object to quad tree                             */
/************************************************************************/
void CQuadTree::AddObject(CCObject* object)
{
	AddObject(m_root,object);
}
/************************************************************************/
/*                  Free a node in quad tree                            */
/************************************************************************/
void CQuadTree::Free(QuadNode* root)
{
	m_root->m_objectsList->m_count = 0;
	if(m_root->m_topLeft)
	{
		Free(m_root->m_topLeft);
	}
	if(m_root->m_topRight)
	{
		Free(m_root->m_topRight);
	}
	if(m_root->m_bottomLeft)
	{
		Free(m_root->m_bottomLeft);
	}
	if(m_root->m_bottomRight)
	{
		Free(m_root->m_bottomRight);
	}
}
/************************************************************************/
/*                         Free entire quad tree                        */
/************************************************************************/
void CQuadTree::Free()
{
	Free(m_root);
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
void AddObjectInRect(ListNodes* objectsList,QuadNode* node, RECT rect)
{
	if(node)
	{
		if(CheckCollisionBetween2Rect(rect,node->m_rect))
		{
			if(node->m_objectsList->m_head)
			{
				objectsList->AddList(node->m_objectsList);
			}
			AddObjectInRect(objectsList,node->m_topLeft,rect);
			AddObjectInRect(objectsList,node->m_bottomLeft,rect);
			AddObjectInRect(objectsList,node->m_topRight,rect);
			AddObjectInRect(objectsList,node->m_bottomRight,rect);
		}
	}
}

bool CheckNodeCollideWithList(Node* node,ListNodes* objectsList)
{
	Node* temp = objectsList->m_head;		
	while (temp != objectsList->m_tail->m_nextNode)
	{
		if(node->m_object->m_canCollide == true &&
			node->m_object->m_style > '0' &&
			CheckCollisionBetween2Rect(node->m_object->m_rect,temp->m_object->m_rect) &&
			node != temp)
		{
			return true;
		}
		temp = temp->m_nextNode;
	}
	return false;
}

bool CheckRectCollideWithList(RECT rect, ListNodes* objectsList)
{
	Node* temp = objectsList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_canCollide == true &&
			temp->m_object->m_style > '0' &&
			CheckCollisionBetween2Rect(rect,temp->m_object->m_rect))
		{
			return true;
		}
		temp = temp->m_nextNode;
		// if temp node reach to the end of list
		// so  exit while loop
		if(temp == objectsList->m_tail->m_nextNode)
		{
			break;
		}
	}
	return false;
}

bool CheckRectCollideWithList(RECT rect, ListNodes* objectsList, char style)
{
	Node* temp = objectsList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_canCollide == true &&
			temp->m_object->m_style == style &&
			CheckCollisionBetween2Rect(rect,temp->m_object->m_rect))
		{
			return true;
		}
		temp = temp->m_nextNode;
	}
	return false;
}

CCObject* ObjectCheckRectWithList(RECT rect, ListNodes* objectsList)
{
	Node* temp = objectsList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_canCollide == true &&
			// temp->m_obhect->Health > 0
			//temp->m_object->m_style != UnitRong &&
			CheckCollisionBetween2Rect(rect,temp->m_object->m_rect))
		{
			return temp->m_object ;
		}
		temp = temp->m_nextNode;
	}
	return NULL;
A}

CCObject* ObjectCheckRectWithList(RECT rect, ListNodes* objectList, char style)
{
	Node* temp = objectList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_style == style &&
			// temp->m_object->heath > 0 &&
			CheckCollisionBetween2Rect(rect,temp->m_object->m_rect))
		{
			return temp->m_object;
		}
		temp = temp->m_nextNode;
	}
	return NULL;
}

CCObject* ObjectCheckRectWithListCheckItems(RECT rect, ListNodes* objectsList)
{
	Node* temp = objectsList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_checkedItem == true &&
		  // temp->m_object->m_style = UnitRong &&
		  CheckCollisionBetween2Rect(rect,temp->m_nextNode->m_object->m_rect)
		{
			return temp->m_object;
		}
		temp = temp->m_nextNode;
	}
	return NULL;
}
#pragma endregion
