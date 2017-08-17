#pragma once
#include "States.h"
#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h> 
#include "ErrorController.h"
#include "TokenController.h"
#include <unordered_map>

#include "LocalNode.h"
#include "GlobalNode.h"
#include "SymbolManager.h"
#include "TypeTableManager.h"

class FSM
{
public:
	FSM();
	~FSM();


	void SetString(char *String);
	void LexicalAnalysis();
	void SintacticalAnalisis();
	void SemanticAnalisis();

	Descriptores::E CheckDescriptor(char character);

	CErrorController ErrorManagment;
	TokenController TokenManagment;
	CSymbolManager SymboolManager;
	CTypeTableManager TypeManager;

	bool Save(std::string file_name);
	bool Load(std::string file_name);

	std::string m_formatString;

	//std::unordered_map<std::string, SubExpr> SubExpresions; // Map de sub expresiones
	//std::unordered_map<std::string, std::vector<Token>> Expresions;
private:

	void Var(Token &target, Category::E Context, std::string FunctionName);
	std::string Expresion(Token &target, Category::E Context, std::string FunctionName, Type::E type);
	void Block(Token &target, Category::E &Context, std::string FuctionName);
	void Assign(Token &target, Category::E &Context, std::string FuctionName);
	char pts;
	int m_iLine;

	Type::E GetTypeByIDToken(Token target);

	char *m_String;

	void Clean();
	

};

