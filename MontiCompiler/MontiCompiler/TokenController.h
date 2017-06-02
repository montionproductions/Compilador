#pragma once
#include <vector>

#include <string>
#include <iostream>
#include <cstring>

#include <iostream>
#include <fstream>

struct Token
{
	std::string Desc;
	std::string Type;
};
class TokenController
{
public:
	TokenController();
	~TokenController();

	bool Save();
	bool Load();

	void PrintTokens();
	void AddToken(std::string Desc, std::string Type);

	void Clean();
private:
	std::vector<Token> m_lTokens;
};

