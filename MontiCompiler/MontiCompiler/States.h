#pragma once
namespace State
{
	enum E
	{
		DEFAULT,
		UNDEF,
		ID,
		INT,
		FLOAT,
		ASING,
		DELIMITER,
		ENDLINE,
		SPACE,
		ARITMETIC_OP,
		OP_AGRUPATION_OP,
		CL_AGRUPATION_OP,
		COMMENT,
		RELATIONSHIP_OP,
		LOGICAL_OP,
		CONST_AF
	};
}

namespace Descriptores
{
	enum E
	{
		Undef,
		Space,
		EndLine, // \n
		Letter, // a,b,c...z
		Digit, // 0,1,2...9
		Point, // .
		Comma, // ,
		TwoPoints, // :
		Semicolon, // ;
		Underscore, // _
		Equal, // =
		Plus, //+
		Less, //-
		Mul, //*
		Divide, // /
		Module, // %
		Exp, // ^
		Op_P, // (
		Cl_P, // )
		Op_Key, // {
		Cl_Key, // }
		Op_Brack, // [
		Cl_Brack, // ]
		LessThan, // <
		GreaterThan, // >
		Exclamation, // !
		Ampersand, // &
		Or, // |
		Const_Af // "
		
	};
}