#include "TokenController.h"
#include "States.h"

TokenController::TokenController()
{
	indexToken = 0;
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

			AddToken(desc, type, IDToken::ID, 0);
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

void TokenController::AddToken(std::string Desc, std::string Type, IDToken::E id, int nLine)
{
	Token token;
	token.ID = id;
	token.Desc = Desc;
	token.Type = Type;
	token.nLine = nLine;

	std::vector<Token>::iterator it = m_lTokens.end();
	m_lTokens.insert(it, token);
}

void TokenController::Clean()
{
	m_lTokens.clear();
}

int TokenController::GetSize()
{
	return m_lTokens.size();
}

Token TokenController::NextToken()
{
	if(m_lTokens.size() > indexToken)
		return m_lTokens[indexToken++];
	else
	{
		printf("No hay mas tokens");
		return m_lTokens.back();
	}
}

Token TokenController::PreviousToken()
{
	if(indexToken > 0)
		return m_lTokens[--indexToken];
	else
	{
		printf("Final token\n");
		return m_lTokens.back();
	}
}

Token TokenController::PanicMode(std::string element)
{
	Token aux = NextToken();
	while (aux.Desc != element)
	{
		aux = NextToken();
	}
	return aux;
}

Token TokenController::GetToken(int index)
{
	indexToken = index;
	return m_lTokens[index];
}
