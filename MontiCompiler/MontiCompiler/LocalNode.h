#pragma once
#include "EnumNodes.h"
#include <string>
#include <fstream>

class CLocalNode
{
public:
	CLocalNode();
	~CLocalNode();

	Category::E m_category;
	Type::E m_type;
	unsigned int m_iDimention;
	std::string m_context_name;
	void *ptrVal;
	//CLocalNode *ptrLocal;
	CLocalNode *ptrNext;

	void Save(std::ofstream *file);
};

