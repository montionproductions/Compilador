#pragma once
#include "States.h"
#include <string>
#include <iostream>
#include <cstring>
#include <stdlib.h> 
#include "ErrorController.h"
#include "TokenController.h"

class FSM
{
public:
	FSM();
	~FSM();


	void SetString(char *String);
	void LexicalAnalysis();

	Descriptores::E CheckDescriptor(char character);

	CErrorController ErrorManagment;
	TokenController TokenManagment;

	bool Save(std::string file_name);
	bool Load(std::string file_name);

	std::string m_formatString;
private:
	char pts;
	int m_iLine;

	char *m_String;

	void Clean();
	

};

