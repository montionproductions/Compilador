#pragma once

#include <vector>
#include <unordered_map>

#include "GlobalNode.h"
#include "LocalNode.h"

#include "EnumNodes.h"
#include "ErrorController.h"
#include "TokenController.h"

class CSymbolManager
{
public:
	CSymbolManager();
	~CSymbolManager();

	void AddVar(std::string name, std::string functionName, Category::E category, Type::E type, int dimension, CLocalNode *ptrLocal, CGlobalNode * ptrGlobal);
	bool FindElement(std::string name);

	void SetControllers(CErrorController *errorManager, TokenController *tokenManager);
private:
	CErrorController *ErrorManagment;
	TokenController *TokenManagment;
	std::unordered_map<std::string, CGlobalNode*> HashMap;
};

