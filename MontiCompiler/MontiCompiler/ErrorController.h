#pragma once
#include <vector>

#include <string>
#include <iostream>
#include <cstring>

#include <iostream>
#include <fstream>


struct Error 
{
	int line;
	std::string type;
	std::string desc;
	std::string text;
};

class CErrorController
{
public:
	CErrorController();
	~CErrorController();

	bool Save();

	void PrintErrors(); // implementar metodo funcional

	void AddError(int line, std::string type, std::string desc, std::string text);

	void Clean();

	std::vector<Error> m_lErrors;
private:
	
};

