#pragma once
#include "CObject.h"
#include <stdlib.h>
class Node
{
public:
	/************************************************************************/
	/*                          Public variables                            */
	/************************************************************************/
	CCObject* m_object;
	Node* m_nextNode;
	/************************************************************************/
	/*                             Constructor                              */
	/************************************************************************/
	Node(CCObject* object)
	{
		m_object = object;
		m_nextNode = NULL;
	}
};

class ListNodes
{
public:
	/************************************************************************/
	/*                          Public variables                            */
	/************************************************************************/
	// Head node of list
	Node* m_head;
	// Tail node of list
	Node* m_tail;
	// Count qualities of nodes in list
	int m_count;
	/************************************************************************/
	/*                             Constructor                              */
	/************************************************************************/
	// Constructor
	ListNodes()
	{
		m_head = NULL;
		m_tail = NULL;
		m_count = 0;
	}
	// Add a node to list
	void AddNode(CCObject* object)
	{
		if(m_head == NULL)
		{
			m_head = new Node(object);
			m_tail = m_head;
			m_count++;
		}
		else
		{
			Node* node = new Node(object);
			m_tail->m_nextNode = node;
			m_tail = node;
			m_count++;
		}
	}
	// Add a another list to current list
	void AddList(ListNodes* list)
	{
		if(m_head == NULL)
		{
			m_head = list->m_head;
			m_tail = list->m_tail;
			m_count = list->m_count;
			m_tail->m_nextNode = NULL;
			return;
		}
		else
		{
			m_tail->m_nextNode = list->m_head;
			m_tail = list->m_tail;
			m_tail->m_nextNode = NULL;
			m_count += list->m_count;
		}
	}
	// Reset list object
	void ResetListObject()
	{
		m_head = NULL;
		m_tail = NULL;
		m_count = 0;
	}
	// Free a nodes list
	void Free()
	{
		Node* temp;
		if(m_head != NULL)
		{
			temp = m_head->m_nextNode;
			while(temp->m_nextNode != NULL)
			{
				Node* temp_2 = temp;
				temp = temp->m_nextNode;
				free(temp_2);
			}
		}
	}
};