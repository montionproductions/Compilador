#include "TypeTableManager.h"
#include "SymbolManager.h"
#include "ErrorController.h"

CTypeTableManager::CTypeTableManager()
{
}


CTypeTableManager::~CTypeTableManager()
{
}

void CTypeTableManager::SetSymbolManager(CSymbolManager * sybolManagerPtr)
{
	m_ptrSymbolManager = sybolManagerPtr;
}

void CTypeTableManager::SetErrorControler(CErrorController * errorController)
{
	m_ptrErrorController = errorController;
}

void CTypeTableManager::AddSubExp(std::string id, SubExpr subExp)
{
	SubExpresions.insert({ { id, subExp } });
}

void CTypeTableManager::AddExp(std::string id, std::vector<Token> expresion)
{
	Expresions.insert({ { id, expresion } });
}

void CTypeTableManager::AddElement(std::string ID, Type::E type, int nLine)
{
	RType r;
	r.type = type;
	r.nLine = nLine;
	Elements.insert({ {ID, r} });
}

void CTypeTableManager::AddDimensionTest(std::string IDvar, std::string IDexpr, Category::E context)
{
	Dimension D;
	D.context = context;
	D.IDvar = IDvar;
	D.IDexpr = IDexpr;
	DC.insert({ {IDvar, D} });
}

void CTypeTableManager::AddAssignation(std::string IDvar, std::string IDexpr)
{
	Asign a;
	a.IDexpr = IDexpr;
	a.IDvar = IDvar;
	vAssignations.push_back(a);
}

void CTypeTableManager::CreateTree(NodeExpr *nodeExpr, Op::E Opertator, Type::E ReturnType)
{
	CSTree Tree;
	Tree.root.Operator = Opertator;
	Tree.root.ptrNode1 = nodeExpr;
	Tree.root.ptrNode2 = 0;
	Tree.root.resultNodo = ReturnType;
	vTrees.push_back(Tree);
}

void CTypeTableManager::CheckSubExp()
{
	for (auto &sub : SubExpresions)
	{
		for (auto &term : sub.second.Expr)
		{
			if (term.ID == IDToken::ID) // Si es ID buscar en SymbolTable
			{
				CGlobalNode *nodo = m_ptrSymbolManager->FindElement(term.Desc);
				if (nodo == NULL)
					m_ptrErrorController->AddError(sub.second.nLine, "<sem>", term.Desc, "variable indefinida");
				else {
					term.returnType = nodo->m_type;
					if (nodo->ptrVar != NULL)
					{
						if (nodo->m_type == Type::INT)
						{
							term.intVar = *(int*)(nodo->ptrVar);
							term.returnType = Type::INT;
						}
						else if (nodo->m_type == Type::FLOAT)
						{
							term.floatVar = *(float*)(nodo->ptrVar);
							term.returnType = Type::FLOAT;
						}
					}
					/*else
					{
						m_ptrErrorController->AddError(sub.second.nLine, "<sem>", term.Desc, "variable sin asignar");
					}*/

				}
			}
			else if (term.ID == IDToken::INT)
			{
				term.returnType = Type::INT;
				term.intVar = atoi(term.Desc.c_str());
			}
			else if (term.ID == IDToken::FLOAT)
			{
				term.returnType = Type::FLOAT;
				term.floatVar = atof(term.Desc.c_str());
			}
			else if (term.ID == IDToken::STRING)
				term.returnType = Type::STRING;
		}

		for (int i = 0; i < sub.second.Expr.size(); i++)
		{
			if (sub.second.Expr[i].ID == IDToken::ARITMETIC_OP)
				sub.second.returnType = sub.second.Expr[i - 1].returnType;
			else if (sub.second.Expr[i].ID == IDToken::RELATIONSHIP_OP)
				sub.second.returnType = Type::BOOLEAN;
		}

		
	}
}

void CTypeTableManager::CheckExpresions()
{
	for (auto &ex: Expresions)
	{
		for (auto &subS : ex.second)
		{
			SubExpr sub = GetSubExpresion(subS.Desc);
			if (sub.Expr.size() > 0)
			{
				ex.second.front().returnType = sub.Expr.front().returnType;
			}
		}
	}
}

void CTypeTableManager::CheckAssign()
{
	std::vector<float> fVals;
	std::vector<int> iVals;

	std::vector<std::string> IDvals;

	std::vector<Op::E> opers;

	for (auto &asign : vAssignations)
	{
		Type::E tipo = Type::INDEF;
		std::vector<Token> Expr = GetExpresion(asign.IDexpr);

		CGlobalNode *var = m_ptrSymbolManager->FindElement(asign.IDvar);
		if (var != NULL)
		{
			if (Expr.size() > 0)
			{
				for (auto ex : Expr)
				{
					if (ex.ID == IDToken::INT)
					{
						iVals.push_back(atoi(ex.Desc.c_str()));
						int id = iVals.size() - 1;
						IDvals.push_back("i" + std::to_string(id));
						if (var->m_type != Type::INT)
							m_ptrErrorController->AddError(ex.nLine, "<sem>", ex.Desc, "tipo incompatible");
					}
					else if (ex.ID == IDToken::FLOAT)
					{
						fVals.push_back(atof(ex.Desc.c_str()));
						int id = fVals.size() - 1;
						IDvals.push_back("f" + std::to_string(id));
						if (var->m_type != Type::FLOAT)
							m_ptrErrorController->AddError(ex.nLine, "<sem>", ex.Desc, "tipo incompatible");
					}
					else if (ex.ID == IDToken::ID)
					{
						CGlobalNode *v = m_ptrSymbolManager->FindElement(ex.Desc);
						if (v == NULL)
							m_ptrErrorController->AddError(ex.nLine, "<sem>", ex.Desc, "variable indefinida");
						else
						{
							if (var->m_type != v->m_type)
								m_ptrErrorController->AddError(ex.nLine, "<sem>", ex.Desc, "tipo incompatible");

							if (v->m_type == Type::FLOAT)
							{
								if (v->ptrVar == NULL)
									m_ptrErrorController->AddError(ex.nLine, "<sem>", ex.Desc, "variable indefinida");
								else
								{
									fVals.push_back(*(float*)(v->ptrVar));
									int id = fVals.size() - 1;
									IDvals.push_back("f" + std::to_string(id));
								}
							}
							else if (v->m_type == Type::INT)
							{
								if (v->ptrVar == NULL)
									m_ptrErrorController->AddError(ex.nLine, "<sem>", ex.Desc, "variable indefinida");
								else
								{
									iVals.push_back(*(int*)(v->ptrVar));
									int id = iVals.size() - 1;
									IDvals.push_back("i" + std::to_string(id));
								}
							}
						}
					}
					else
					{
						SubExpr sub = GetSubExpresion(ex.Desc);
						if (sub.Expr.size() > 0)
						{
							for (auto &term : sub.Expr)
							{
								if (term.ID == IDToken::ID) // Si es ID buscar en SymbolTable
								{
									CGlobalNode *nodo = m_ptrSymbolManager->FindElement(term.Desc);
									if (nodo == NULL)
										m_ptrErrorController->AddError(term.nLine, "<sem>", term.Desc, "variable indefinida");
									else {
										tipo = nodo->m_type;
										if (tipo == Type::INT)
										{
											iVals.push_back(*(int*)(nodo->ptrVar));
											int id = iVals.size() - 1;
											std::string s = "i";
											s += id;
											IDvals.push_back(s);
										}
										else if (tipo == Type::FLOAT)
										{
											fVals.push_back(*(float*)(nodo->ptrVar));
											int id = fVals.size() - 1;
											std::string s = "f";
											s += id;
											IDvals.push_back(s);
										}
									}
								}
								else if (term.ID == IDToken::INT)
								{
									tipo = Type::INT;
									iVals.push_back(term.intVar);
								}
								else if (term.ID == IDToken::FLOAT)
								{
									tipo = Type::FLOAT;
									fVals.push_back(term.floatVar);
								}
								else if (term.ID == IDToken::STRING)
									tipo = Type::STRING;
								else if (term.Desc == "*")
									opers.push_back(Op::Mul);
								else if (term.Desc == "/")
									opers.push_back(Op::Division);
								else if (term.Desc == "+")
									opers.push_back(Op::Sum);
								else if (term.Desc == "+")
									opers.push_back(Op::Rest);


							}
						}
					}
				}
			}

			// Resultado final
			int iResult = 0;
			float fResult = 0.0f;

			int i = 0;
			int f = 0;

			for (auto term : IDvals)
			{
				if (term[0] == 'i')
					iResult = iVals[i++];
			}

			var->ptrVar = &iResult;


		}
	}	
}

void CTypeTableManager::CheckDimensions()
{
	for (auto &e : DC)
	{
		if (GetExpresion(e.second.IDexpr).size() > 0)
		{
			std::vector<Token> Expr = GetExpresion(e.second.IDexpr);
			CGlobalNode *node = m_ptrSymbolManager->FindElement(e.second.IDvar);
			Type::E t1 = Expr.front().returnType;
			if (t1 == Type::INT)
			{
				
			}
			else
				m_ptrErrorController->AddError(Expr.front().nLine, "<sem>", node->m_name, "dimension invalidad");
		}
	}
}

void CTypeTableManager::CheckTypes()
{
	for (auto &elemen : Elements)
	{
		if (GetExpresion(elemen.first).size() > 0)
		{
			for (auto exp : GetExpresion(elemen.first))
			{
				if (GetSubExpresion(exp.Desc).Expr.size() > 0)
				{
					for (auto sub : GetSubExpresion(exp.Desc).Expr)
					{
						if (sub.ID == IDToken::ID)
						{
							CGlobalNode *g = m_ptrSymbolManager->FindElement(sub.Desc);
							if (g != NULL)
							{
								if (g->m_type != elemen.second.type)
								{
									m_ptrErrorController->AddError(elemen.second.nLine, "<sem>", g->m_name, "se asigno tipo invalido");
								}
							}
						}
						else if (sub.ID == IDToken::FLOAT || sub.ID == IDToken::INT)
						{
							if (sub.ID != elemen.second.type)
							{
								m_ptrErrorController->AddError(sub.nLine, "<sem>", sub.Desc, "se asigno tipo invalido");
							}
						}
					}
				}
			}
		}
	}
}

std::vector<Token> CTypeTableManager::GetExpresion(std::string exp)
{
	std::unordered_map<std::string, std::vector<Token>>::const_iterator expr = Expresions.find(exp);
	if(expr != Expresions.end())
		return expr->second;
	else
		return std::vector<Token>();
}

SubExpr CTypeTableManager::GetSubExpresion(std::string ID)
{
	std::unordered_map<std::string, SubExpr>::const_iterator sub = SubExpresions.find(ID);
	if (sub != SubExpresions.end())
		return sub->second;
	else
		return SubExpr();
}

/*void *CTypeTableManager::GenerateValueExpr(SubExpr subExp)
{
	if (m_ptrSymbolManager == NULL)
		return nullptr;
	std::vector<std::string> Operators;
	Operators.push_back("*");
	Operators.push_back("/");
	Operators.push_back("+");
	Operators.push_back("-");

	for (auto Op : Operators)
	{
		bool exit = false;
		int limit = 10;
		while (!exit && limit >= 0)
		{
			limit--;
			exit = true;
			for (int term = 0; term < subExp.Expr.size(); term++)
			{
				if (subExp.Expr[term].Desc == Op && subExp.Expr[term].Desc != "~")
				{
					if (!CompareType(subExp, term))
					{
						m_ptrErrorController->AddError(subExp.nLine, "<sem>", subExp.Expr[term].Desc, "El tipo no corresponde");
					}
					exit = false;
				}
			}
		}
	}
	int a = 10;
	return &a;
}*/

/*bool CTypeTableManager::CompareType(SubExpr subExp, int index)
{
	bool r[2];

	r[0] = false;
	r[1] = false;

	if (subExp.Expr[index - 1].ID == IDToken::ID)
	{
		CGlobalNode *nodo = m_ptrSymbolManager->FindElement(subExp.Expr[index - 1].Desc);
		if (nodo == NULL)
			m_ptrErrorController->AddError(subExp.nLine, "<sem>", subExp.Expr[index - 1].Desc, "Indefinido");
		else {
			subExp.Expr[index - 1].Desc = "~";
			if (nodo->m_type == subExp.varType)
				r[0] = true;
		}
	}
	else if (subExp.Expr[index - 1].Type == "Int" || subExp.Expr[index - 1].Type == "Float" || subExp.Expr[index - 1].Type == "Bool"
		|| subExp.Expr[index - 1].Type == "Boolean" || subExp.Expr[index - 1].Type == "String")
	{
		subExp.Expr[index - 1].Desc = "~";
		r[0] = true;
	}

	if (subExp.Expr[index + 1].ID == IDToken::ID)
	{
		CGlobalNode *nodo = m_ptrSymbolManager->FindElement(subExp.Expr[index - 1].Desc);
		if (nodo == NULL)
			m_ptrErrorController->AddError(subExp.nLine, "<sem>", subExp.Expr[index - 1].Desc, "Indefinido");
		else {
			subExp.Expr[index + 1].Desc = "~";
			if (nodo->m_type == subExp.varType)
				r[1] = true;
		}
	}
	else if (subExp.Expr[index + 1].Type == "Int" || subExp.Expr[index + 1].Type == "Float" || subExp.Expr[index + 1].Type == "Bool"
		|| subExp.Expr[index + 1].Type == "Boolean" || subExp.Expr[index + 1].Type == "String")
	{
		subExp.Expr[index + 1].Desc = "~";
		r[1] = true;
	}
	return r[0] && r[1];
}*/
