#pragma once
#include <string>
#include "States.h"
#include <vector>
namespace Type
{
	enum E
	{
		FLOAT,
		INT,
		STRING,
		BOOLEAN,
		INDEF
	};
}

namespace Category
{
	enum E
	{
		Global,
		Local,
		Param,
		Indef,
		Process,
		Function
	};
}

namespace Op
{
	enum E
	{
		//Logicos
		LessThan, // <
		GreaterThan, // <

		//Relacionales
		Equal, // ==

		//Aritmeticos
		Mul, // *
		Division, // /
		Sum, // +
		Rest, // -
		Module // %

	};
}

namespace NodoType
{
	enum E
	{
		Function,
		Constant,
		ID,
		Nodo
	};
}
// Tokens
struct Token
{
	std::string Desc;
	std::string Type;

	IDToken::E ID;
	int nLine;

	Type::E returnType; // asignacion por semantico
	int intVar; // asignacio por semantico
	float floatVar; // asignacio por semantico
};

// Expresion
struct SubExpr
{
	std::string ID;
	std::vector <Token> Expr;
	Type::E varType;
	int nLine;

	Type::E returnType; // Asignacion por semantico
};

// Dimension
struct Dimension
{
	std::string IDvar;
	std::string IDexpr;
	Category::E context;
};

// Revision de tipo
struct RType
{
	Type::E type;
	int nLine;
};

//Asignacion 
struct Asign
{
	std::string IDvar;
	std::string IDexpr;
};