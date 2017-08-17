#pragma once
#include "EnumNodes.h"
#include <string>

// ========================== Expr Node ==========================
class NodeExpr
{
public:
	NodeExpr();
	~NodeExpr();

	Op::E Operator;
	NodeExpr *ptrNode1;
	NodeExpr *ptrNode2;
	Type::E resultNodo;

	float floatVar;
	int intVar;
	bool boolVar;
};

// ======================== Const Node ===============================
class NodeConst
{
public:
	NodeConst();
	~NodeConst();

	NodoType::E NodoType;
	Type::E resultNodo;

	std::string ID;
	std::string Const;
	NodeExpr* ptrNodoExpr;
};

// ========================== Tree class ==========================
class CSTree
{
public:
	CSTree();
	~CSTree();

	NodeExpr root;
	int intVal;
	float floatVal;
	std::string stringVal;
	bool boolVal;
};