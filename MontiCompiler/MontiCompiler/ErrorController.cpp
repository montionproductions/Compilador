#include "ErrorController.h"


CErrorController::CErrorController()
{
}


CErrorController::~CErrorController()
{
}

bool CErrorController::Save()
{
	std::ofstream myfile;

	myfile.open("Errores.err", std::ios::binary);
	if (myfile.is_open())
	{
		myfile << m_lErrors.size();
		for (auto err : m_lErrors)
		{
			myfile << err.desc << " " << err.line << " " << err.text << " " << err.type << std::endl;
		}

		myfile.close();
	}
	else
		return true;
}

void CErrorController::PrintErrors()
{
	for (auto error : m_lErrors)
	{
		std::cout << "\"" << error.text << "\" : " << error.desc << ", Line: " << error.line << ", Type: " <<error.type << std::endl;
	}
}

void CErrorController::AddError(int line, std::string type, std::string desc, std::string text)
{
	Error newError;
	newError.line = line;
	newError.type = type;
	newError.desc = desc;
	newError.text = text;

	m_lErrors.push_back(newError);
}

void CErrorController::Clean()
{
	m_lErrors.clear();
}
