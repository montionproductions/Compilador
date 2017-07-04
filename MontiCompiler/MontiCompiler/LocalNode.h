#pragma once
#include "EnumNodes.h"
class CLocalNode
{
public:
	CLocalNode();
	~CLocalNode();

	Category::E m_category;
	Type::E m_type;
	unsigned int m_iDimention;
	char* m_context_name;
	CLocalNode *ptrLocal;
	CLocalNode *ptrNext;
};

