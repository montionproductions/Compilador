#pragma once
#include <vector>

#include <string>
#include <iostream>
#include <cstring>

#include <iostream>
#include <fstream>
#include "States.h"
#include "EnumNodes.h"

struct Token
{
	std::string Desc;
	std::string Type;

	IDToken::E ID;
	int nLine;
};
class TokenController
{
public:
	TokenController();
	~TokenController();

	bool Save();
	bool Load();

	void PrintTokens();
	void AddToken(std::string Desc, std::string Type, IDToken::E id, int nLine);

	void Clean();

	int GetSize();
	int indexToken;
	Token NextToken();
	Token PreviousToken();

	Token PanicMode(std::string element);

	Token GetToken(int index);
private:
	std::vector<Token> m_lTokens;
};

