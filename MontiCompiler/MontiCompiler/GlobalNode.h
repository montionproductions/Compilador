#pragma once
#include "EnumNodes.h"
#include "LocalNode.h"
class CGlobalNode
{
public:
	CGlobalNode();
	~CGlobalNode();

	char* m_name;
	Category::E m_category;
	Type::E m_type;
	unsigned int m_iDimension;
	void *ptrVar;
	CLocalNode *ptrLocal;
	CGlobalNode *ptrNext;
};

