#pragma once
#include "EnumNodes.h"
#include <string>

class CLocalNode
{
public:
	CLocalNode();
	~CLocalNode();

	Category::E m_category;
	Type::E m_type;
	unsigned int m_iDimention;
	std::string m_context_name;
	CLocalNode *ptrLocal;
	CLocalNode *ptrNext;
};

