#pragma once
#include "States.h"
#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h> 
#include "ErrorController.h"
#include "TokenController.h"

#include "LocalNode.h"
#include "GlobalNode.h"
#include "SymbolManager.h"

class FSM
{
public:
	FSM();
	~FSM();


	void SetString(char *String);
	void LexicalAnalysis();
	void SintacticalAnalisis();

	Descriptores::E CheckDescriptor(char character);

	CErrorController ErrorManagment;
	TokenController TokenManagment;
	CSymbolManager SymboolManager;

	bool Save(std::string file_name);
	bool Load(std::string file_name);

	std::string m_formatString;
private:

	void Var(Token &target, Category::E Context, std::string FunctionName);
	void Expresion(Token &target, Category::E Context, std::string FunctionName);
	void Block(Token &target, Category::E &Context, std::string FuctionName);
	void Assign(Token &target, Category::E &Context, std::string FuctionName);
	char pts;
	int m_iLine;

	char *m_String;

	void Clean();
	

};

