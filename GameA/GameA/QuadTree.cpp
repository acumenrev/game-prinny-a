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
void CQuadTree::AddObject(QuadNode* node, CCObject* object)
{
	if(node != NULL)
	{
		node->m_count++;
		long topBottom = (node->m_rect.top + node->m_rect.bottom)/2;
		long leftRight = (node->m_rect.left + node->m_rect.right)/2;
		RECT temp;
		// Check in Top Left
		temp.top = node->m_rect.top;
		temp.bottom = topBottom;
		temp.left = node->m_rect.left;
		temp.right = leftRight;
		// Check TEMP rect stays in another rect
		if(CheckStayInAnotherRect(object->m_workingArea,temp) && node->m_level < MAXNODE)
		{
			if(!node->m_topLeft)
			{
				node->m_topLeft = new QuadNode(temp);
			}
			node->m_topLeft->m_level = node->m_level + 1;
			return AddObject(node->m_topLeft,object);
		}
		// Check in Bottom Left
		temp.top = topBottom;
		temp.bottom = node->m_rect.bottom;
		temp.left = node->m_rect.left;
		temp.right = leftRight;
		// Check TEMP rect stays in another rect
		if(CheckStayInAnotherRect(object->m_workingArea,temp) && node->m_level < MAXNODE)
		{
			if(!node->m_bottomLeft)
			{
				node->m_bottomLeft = new QuadNode(temp);
			}
			node->m_bottomLeft->m_level = node->m_level + 1;
			return AddObject(node->m_bottomLeft,object);
		}
		// Check in Right top
		temp.top = node->m_rect.top;
		temp.bottom = topBottom;
		temp.left = leftRight;
		temp.right = node->m_rect.right;
		// Check TEMP rect stays in another rect
		if(CheckStayInAnotherRect(object->m_workingArea,temp) && node->m_level < MAXNODE)
		{
			if(!node->m_topRight)
			{
				node->m_topRight = new QuadNode(temp);
			}
			node->m_topRight->m_level = node->m_level + 1;
			return AddObject(node->m_topRight,object);
		}
		// Check in Bottom Right
		temp.top = topBottom;
		temp.bottom = node->m_rect.bottom;
		temp.left = leftRight;
		temp.right = node->m_rect.right;
		// Check TEMP rect stays in another rect
		if(CheckStayInAnotherRect(object->m_workingArea,temp) && node->m_level < MAXNODE)
		{
			if(!node->m_bottomRight)
			{
				node->m_bottomRight = new QuadNode(temp);
			}
			node->m_bottomRight->m_level = node->m_level + 1;
			return AddObject(node->m_bottomRight, object);
		}
		// Assign object
		node->m_objectsList->AddNode(object);
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
void CQuadTree::Free(QuadNode* node)
{
	node->m_objectsList->m_count = 0;
	if(node->m_topLeft)
	{
		Free(node->m_topLeft);
	}
	if(node->m_topRight)
	{
		Free(node->m_topRight);
	}
	if(node->m_bottomLeft)
	{
		Free(node->m_bottomLeft);
	}
	if(m_root->m_bottomRight)
	{
		Free(node->m_bottomRight);
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
/*                          Set health for a node                       */
/************************************************************************/
void CQuadTree::SetHealth(QuadNode* node)
{

}
/************************************************************************/
/*                          Set health for entire list                  */
/************************************************************************/
void CQuadTree::SetHealth()
{
	SetHealth(m_root);
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
/************************************************************************/
/*                                                                      */
/************************************************************************/
bool CheckNodeCollideWithList(Node* node,ListNodes* objectsList)
{
	Node* temp = objectsList->m_head;		
	while (temp != objectsList->m_tail->m_nextNode)
	{
		if(temp->m_object->m_canCollide == true &&
			temp->m_object->m_health > 0 &&
			temp->m_object->m_style > '0' &&
			CheckCollisionBetween2Rect(node->m_object->m_rect,temp->m_object->m_rect) &&
			node != temp)
		{
			return true;
		}
		temp = temp->m_nextNode;
	}
	return false;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
bool CheckRectCollideWithList(RECT rect, ListNodes* objectsList)
{
	Node* temp = objectsList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_canCollide == true &&
			temp->m_object->m_health > 0 &&
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
/************************************************************************/
/*                                                                      */
/************************************************************************/
bool CheckRectCollideWithList(RECT rect, ListNodes* objectsList, char style)
{
	Node* temp = objectsList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_canCollide == true &&
			temp->m_object->m_health > 0  &&
			temp->m_object->m_style == style &&
			CheckCollisionBetween2Rect(rect,temp->m_object->m_rect))
		{
			return true;
		}
		temp = temp->m_nextNode;
	}
	return false;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
CCObject* ObjectCheckRectWithList(RECT rect, ListNodes* objectsList)
{
	Node* temp = objectsList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_canCollide == true &&
			 temp->m_object->m_health > 0		&&
			 temp->m_object->m_style != UNIT_BLANK &&
			CheckCollisionBetween2Rect(rect,temp->m_object->m_rect))
		{
			return temp->m_object ;
		}
		temp = temp->m_nextNode;
	}
	return NULL;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
CCObject* ObjectCheckRectWithList(RECT rect, ListNodes* objectList, char style)
{
	Node* temp = objectList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_style == style &&
			 temp->m_object->m_health > 0 &&
			CheckCollisionBetween2Rect(rect,temp->m_object->m_rect))
		{
			return temp->m_object;
		}
		temp = temp->m_nextNode;
	}
	return NULL;
}
/************************************************************************/
/*                                                                      */
/************************************************************************/
CCObject* ObjectCheckRectWithListCheckItems(RECT rect, ListNodes* objectsList)
{
	Node* temp = objectsList->m_head;
	while(temp != NULL)
	{
		if(temp->m_object->m_checkedItem == true &&
			temp->m_object->m_health > 0 &&
			temp->m_object->m_style == UNIT_BLANK &&
		  CheckCollisionBetween2Rect(rect,temp->m_nextNode->m_object->m_rect))
		{
			return temp->m_object;
		}
		temp = temp->m_nextNode;
	}
	return NULL;
}
#pragma endregion
