#include "SymbolManager.h"



CSymbolManager::CSymbolManager()
{
}

CSymbolManager::~CSymbolManager()
{
}

void CSymbolManager::AddVar(std::string name, std::string functionName, Category::E category, Type::E type, int dimension, CLocalNode *ptrLocal, CGlobalNode * ptrGlobal)
{
	CGlobalNode *global = new CGlobalNode();
	CLocalNode *local = new CLocalNode();

	if (!FindElement(name))
	{
		if (category == Category::Global || category == Category::Process || category == Category::Function)
		{
			global->m_name = name;
			global->m_category = category;
			global->m_iDimension = dimension;
			global->m_type = type;
			global->ptrVar = NULL;
			global->ptrLocal = NULL;
			global->ptrNext = NULL;

		}
		else if (category == Category::Param)
		{
			global->m_name = name;
			global->m_category = Category::Indef;
			global->m_iDimension = 0;
			global->m_type = Type::INDEF;
			global->ptrVar = NULL;

			local->m_category = category;
			local->m_type = type;
			local->m_iDimention = dimension;
			local->m_context_name = functionName;
			local->ptrLocal = NULL;
			local->ptrNext = NULL;
			global->ptrLocal = local;

			global->ptrNext = NULL;
		}
		else if (category == Category::Local)
		{
			global->m_name = name;
			global->m_category = Category::Indef;
			global->m_iDimension = 0;
			global->m_type = Type::INDEF;
			global->ptrVar = NULL;

			local->m_category = category;
			local->m_type = type;
			local->m_iDimention = dimension;
			local->m_context_name = functionName;
			local->ptrLocal = NULL;
			local->ptrNext = NULL;
			global->ptrLocal = local;

			global->ptrNext = NULL;
		}
		HashMap.insert({ {name, global} });
	}
	else
	{
		if (category == Category::Global || category == Category::Process)
			ErrorManagment->AddError(0, "<sint>", name, "Redefinición de variable");
		else if(category == Category::Param)
		{

		}
	}

}

bool CSymbolManager::FindElement(std::string name)
{
	if (HashMap.find(name) != HashMap.end())
		return true;
	return false;
}

void CSymbolManager::SetControllers(CErrorController *errorManager, TokenController *tokenManager)
{
	ErrorManagment = errorManager;
	TokenManagment = tokenManager;
}

bool CSymbolManager::Save()
{
	std::ofstream myfile;

	myfile.open("Simbolos.symb", std::ios::binary);
	if (myfile.is_open())
	{
		myfile << HashMap.size() << " ";

		for (auto token : HashMap)
		{
			myfile << token.second->GetInfo() << "           ";
		}

		myfile.close();
	}
	else
		return true;
}

void CSymbolManager::Reset()
{
	TokenManagment->indexToken = 0;
	HashMap.clear();
}

