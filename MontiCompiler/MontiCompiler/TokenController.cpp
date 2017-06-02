#include "TokenController.h"


TokenController::TokenController()
{
}


TokenController::~TokenController()
{
}

bool TokenController::Save()
{
	std::ofstream myfile;

	myfile.open("Tokens.lex", std::ios::binary);
	if (myfile.is_open())
	{
		myfile << m_lTokens.size();
		for (auto token : m_lTokens)
		{
			myfile << token.Desc << " " << token.Type << " ";
		}

		myfile.close();
	}
	else
		return true;
}

bool TokenController::Load()
{
	std::ifstream myfile;

	myfile.open("Tokens.lex", std::ios::binary);
	if (myfile.is_open())
	{
		int nTokens = 0;
		myfile >> nTokens;
		for (int i = 0; i < nTokens; i++)
		{
			std::string desc;
			std::string type;
			myfile >> desc >> type;

			AddToken(desc, type);
		}

		myfile.close();
	}
	else
		return true;
}

void TokenController::PrintTokens()
{
	for (auto &token : m_lTokens)
		std::cout << "Token " << token.Type << ": " << token.Desc << std::endl;
}

void TokenController::AddToken(std::string Desc, std::string Type)
{
	Token token;
	token.Desc = Desc;
	token.Type = Type;
	m_lTokens.push_back(token);
}

void TokenController::Clean()
{
	m_lTokens.clear();
}
