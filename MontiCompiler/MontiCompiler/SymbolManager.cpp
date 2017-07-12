#include "SymbolManager.h"



CSymbolManager::CSymbolManager()
{
}

CSymbolManager::~CSymbolManager()
{
}

void CSymbolManager::AddVar(std::string name, std::string functionName, Category::E category, Type::E type, int dimension, CLocalNode *ptrLocal, CGlobalNode * ptrGlobal)
{
	CGlobalNode global;
	CLocalNode local;
	CLocalNode param;

	if (!FindElement(name))
	{
		if (category == Category::Global)
		{
			global.m_name = name;
			global.m_category = category;
			global.m_iDimension = dimension;
			global.m_type = type;
			global.ptrVar = NULL;
			global.ptrLocal = NULL;
			global.ptrNext = NULL;

		}
		else if (category == Category::Local)
		{
			global.m_name = name;
			global.m_category = Category::Indef;
			global.m_iDimension = 0;
			global.m_type = Type::INDEF;
			global.ptrVar = NULL;

			local.m_category = category;
			local.m_type = type;
			local.m_iDimention = dimension;
			local.m_context_name = functionName;
			local.ptrLocal = NULL;
			local.ptrNext = NULL;
			global.ptrLocal = &local;

			global.ptrNext = NULL;
		}
		HashMap.insert({ {name, global} });
	}

}

bool CSymbolManager::FindElement(std::string name)
{
	if (HashMap.find(name) != HashMap.end())
		return true;
	return false;
}
