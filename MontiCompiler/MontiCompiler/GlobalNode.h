#pragma once
#include "EnumNodes.h"
#include "LocalNode.h"
#include <fstream>
class CGlobalNode
{
public:
	CGlobalNode();
	~CGlobalNode();

	std::string m_name;
	Category::E m_category;
	Type::E m_type;
	unsigned int m_iDimension;
	void *ptrVar;
	CLocalNode *ptrLocal;
	CGlobalNode *ptrNext;

	void Save(std::ofstream *file);
};

