#pragma once
#include <unordered_map>
#include "EnumNodes.h"
#include "STree.h"
class CSymbolManager;
class CErrorController;
class CTypeTableManager
{
public:
	CTypeTableManager();
	~CTypeTableManager();
	
	void SetSymbolManager(CSymbolManager *sybolManagerPtr);
	CSymbolManager *m_ptrSymbolManager;

	void SetErrorControler(CErrorController *errorController);
	CErrorController *m_ptrErrorController;

	void AddSubExp(std::string id, SubExpr subExp);
	void AddExp(std::string id, std::vector<Token> expresion);
	void AddElement(std::string ID, Type::E type, int nLine);
	void AddDimensionTest(std::string IDvar, std::string IDexpr, Category::E context);
	void AddAssignation(std::string IDvar, std::string IDexpr);

	std::vector<CSTree> vTrees;
	void CreateTree(NodeExpr *nodeExpr, Op::E Opertator, Type::E ReturnType);

	void CheckSubExp();
	void CheckExpresions();
	void CheckAssign();
	void CheckDimensions();
	void CheckTypes();

	std::vector<Token> GetExpresion(std::string);
	SubExpr GetSubExpresion(std::string);

private:
	//void *GenerateValueExpr(SubExpr subExp);
	//bool CompareType(SubExpr subExp, int index);

	std::unordered_map<std::string, RType> Elements; // contiene las pruebas de tipo que se deben hacer
	std::unordered_map<std::string, Dimension> DC; // Comprobacion de dimenciones

	// ======================= Arboles semanticos =======================================
	std::unordered_map<std::string, std::vector<Token>> Expresions; /// Arboles semanticos
	std::unordered_map<std::string, SubExpr> SubExpresions; // Map de sub expresiones

	std::vector<Asign> vAssignations; // contiene las asignaciones que se deben hacer
	
	
};

