#include "FSM.h"


FSM::FSM()
{
	SymboolManager.SetControllers(&ErrorManagment, &TokenManagment);
	m_iLine = 0;
}


FSM::~FSM()
{
}

void FSM::SetString(char *String)
{
	Clean();
	m_String = "";

	m_String = (char*)malloc(std::strlen(String) + 1);
	sprintf(m_String, "%s ", &String[0]);

	m_formatString = m_String;
}

void FSM::LexicalAnalysis()
{
	pts = m_String[0];

	std::string Token;

	State::E state = State::DEFAULT;
	Descriptores::E desc = CheckDescriptor(pts);
	int nLine = 1;
	
	bool openComment = false;
	bool openConstAf = false;

	while (pts != NULL)
	{
	
		switch (state)
		{

		case State::DEFAULT:
		{
			switch (desc)
			{
			case Descriptores::EndLine:
			{
				state = State::ENDLINE;
				m_String--;
			}
				break;

			case Descriptores::Letter:
			case Descriptores::Underscore:
				state = State::ID;
			break;

			case Descriptores::Digit:
				state = State::INT;
			break;

			case Descriptores::TwoPoints:
			case Descriptores::Comma:
			case Descriptores::Semicolon:
				state = State::DELIMITER;
			break;

			case Descriptores::Point:
				state = State::FLOAT;
				break;

			case Descriptores::Space:
			case Descriptores::Tap:
				state = State::SPACE;
				break;

			case Descriptores::Equal:
				state = State::ASING;
				break;

			case Descriptores::Plus:
			case Descriptores::Less:
			case Descriptores::Mul:
			case Descriptores::Divide:
			case Descriptores::Module:
			case Descriptores::Exp:
				state = State::ARITMETIC_OP;
				break;

			case Descriptores::Op_P:
			case Descriptores::Op_Key:
			case Descriptores::Op_Brack:
				state = State::OP_AGRUPATION_OP;
				break;

			case Descriptores::Cl_P:
			case Descriptores::Cl_Key:
			case Descriptores::Cl_Brack:
				state = State::CL_AGRUPATION_OP;
				break;

			case Descriptores::LessThan:
			case Descriptores::GreaterThan:
			case Descriptores::Exclamation:
				state = State::RELATIONSHIP_OP;
				break;

			case Descriptores::Ampersand:
			case Descriptores::Or:
				state = State::LOGICAL_OP;
				break;

			case Descriptores::Const_Af:
				state = State::CONST_AF;
				break;

			default:
				state = State::UNDEF;
				break;
			}
			Token += pts;
		}
		break;
		case State::UNDEF:
		{
			//Token += pts;
			ErrorManagment.AddError(nLine, "<lex>", Token, "expresion sin definicion");
			memset(&Token, 0, sizeof(Token));
			m_String--;
			state = State::DEFAULT;
		}
		break;
		case State::ENDLINE:
		{
			nLine++;
			memset(&Token, 0, sizeof(Token));
			state = State::DEFAULT;
		}
		break;
		case State::ID:
		{
			if (desc == Descriptores::Letter || desc == Descriptores::Digit || desc == Descriptores::Underscore)
				Token += pts;
			else if (desc == Descriptores::Undef || desc == Descriptores::Point)
			{
				TokenManagment.AddToken(Token, "ID", IDToken::ID, nLine);
				ErrorManagment.AddError(nLine, "<lex>", "indentificador no reconocido", Token + pts);
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;
			}
			else
			{
				if(Token == "float" || Token == "int" || Token == "var" || Token == "string" || Token == "bool" ||
					Token == "boolean" || Token == "function" || Token == "procedure" || Token == "main"||
					Token == "for" || Token == "while" || Token == "if" || Token == "else" || Token == "switch"||
					Token == "default" || Token == "print" || Token == "read" || Token == "return" || Token == "void")
					TokenManagment.AddToken(Token, "Keyword", IDToken::KEYWORD, nLine);
				else
					TokenManagment.AddToken(Token, "ID", IDToken::ID, nLine);
				memset(&Token, 0, sizeof(Token));
				
				m_String--;
				
				state = State::DEFAULT;
			}
		}
		break;
		case State::INT:
		{
			if (desc == Descriptores::Digit)
				Token += pts;
			else if (desc == Descriptores::Undef /*|| desc == Descriptores::Comma*/)
			{
				Token += pts;
				ErrorManagment.AddError(nLine, "<lex>", Token, "expresion sin definicion");
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;
			}
			else if (desc == Descriptores::Point)
			{
				Token += pts;
				state = State::FLOAT;
			}
			else
			{
				TokenManagment.AddToken(Token, "Int", IDToken::INT, nLine);
				memset(&Token, 0, sizeof(Token));
				m_String--;
				state = State::DEFAULT;
			}
		}
		break;
		case State::FLOAT:
		{
			if (desc == Descriptores::Digit && Token != ".")
				Token += pts;
			else if (desc == Descriptores::Undef || desc == Descriptores::Point || desc == Descriptores::Letter || desc == Descriptores::Underscore || Token == "." || Token[Token.size() - 1] == '.')
			{
				Token += pts;
				ErrorManagment.AddError(nLine, "<lex>", "se esperaba un float", Token);
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;
			} 
			else
			{
				TokenManagment.AddToken(Token, "Float", IDToken::FLOAT,nLine);
				memset(&Token, 0, sizeof(Token));
				m_String--;
				state = State::DEFAULT;
			}
		}
		break;
		case State::DELIMITER:
		{
			TokenManagment.AddToken(Token, "Delimiter", IDToken::DELIMITER, nLine);
			m_String--;
			memset(&Token, 0, sizeof(Token));
			state = State::DEFAULT;
		}
		break;
		case State::SPACE:
		{
			memset(&Token, 0, sizeof(Token));
			m_String--;
			state = State::DEFAULT;
		}
		break;

		case State::ASING:
		{
			if (desc == Descriptores::Equal)
			{
				Token += pts;
				TokenManagment.AddToken(Token, "Relationship_Op", IDToken::RELATIONSHIP_OP, nLine);
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;

			}
			else
			{
				TokenManagment.AddToken(Token, "Asignation", IDToken::ASSIGNATION, nLine);
				m_String--;
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;
			}

		}
		break;

		case State::ARITMETIC_OP:
		{
			if (pts != '*')
			{
				TokenManagment.AddToken(Token, "Aritmetic_Op", IDToken::ARITMETIC_OP, nLine);
				m_String--;
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;
			} 
			else
			{
				state = State::COMMENT;
				Token += pts;
				openComment = true;
			}
		}
		break;

		case State::OP_AGRUPATION_OP:
		{
			TokenManagment.AddToken(Token, "Op_Agrup_Op", IDToken::O_AGRUP_OP, nLine);
			m_String--;
			memset(&Token, 0, sizeof(Token));
			state = State::DEFAULT;
		}
		break;

		case State::CL_AGRUPATION_OP:
		{
			TokenManagment.AddToken(Token, "CL_Agrup_Op", IDToken::C_AGRUP_OP, nLine);
			m_String--;
			memset(&Token, 0, sizeof(Token));
			state = State::DEFAULT;
		}
		break;

		case State::COMMENT:
		{
			if ((Token[Token.size() - 1] == '*') && (pts == '/'))
			{
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;
				openComment = false;
			}
			else if (pts == '\n')
				nLine++;
			else
				Token += pts;
		}
		break;

		case State::RELATIONSHIP_OP:
		{
			if (pts == '=')
				Token += pts;
			else
				m_String--;

			if(Token == "!")
				TokenManagment.AddToken(Token, "Logical_Op", IDToken::LOGICAL_OP, nLine);
			else
				TokenManagment.AddToken(Token, "Relationship_Op", IDToken::RELATIONSHIP_OP, nLine);

			memset(&Token, 0, sizeof(Token));
			state = State::DEFAULT;

		}
		break;

		case State::LOGICAL_OP:
		{
			if (pts == '&' || pts == '|')
			{
				Token += pts;
				TokenManagment.AddToken(Token, "Logical_Op", IDToken::LOGICAL_OP, nLine);
			}
			else
				ErrorManagment.AddError(nLine, "<lex>", "se esperaba un operador logico", Token);

			memset(&Token, 0, sizeof(Token));
			state = State::DEFAULT;

		}
			break;

		case State::CONST_AF:
		{
			openConstAf = true;

			if (pts == '"')
			{
				TokenManagment.AddToken(Token, "Const_Af", IDToken::CONST_AF, nLine);
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;
				openConstAf = false;
			} 
			else if (pts == '\n')
			{
				ErrorManagment.AddError(nLine, "<lex>", "falto cerrar comillas", "\"");
				memset(&Token, 0, sizeof(Token));
				state = State::DEFAULT;
				openConstAf = false;
			}
			else if (Token == "\"")
			{
				memset(&Token, 0, sizeof(Token));
				Token += pts;
			}
			else
				Token += pts;


		}
			break;

		}

		m_String++;
		pts = m_String[0];
		desc = CheckDescriptor(pts);
	}

	if (openComment)
		ErrorManagment.AddError(nLine, "<lex>", "comentario no cerrado al final del archivo", "/*");

	if(openConstAf)
		ErrorManagment.AddError(nLine, "<lex>", "falto cerrar comillas", "\"");

	ErrorManagment.PrintErrors();
	TokenManagment.PrintTokens();
}

void FSM::SintacticalAnalisis()
{
	Token target;

	Category::E Context = Category::Global;

	/*std::vector<CGlobalNode> vGlobals;
	std::vector<CLocalNode> vLocals;
	std::vector<CLocalNode> vParams;*/

	Type::E type = Type::FLOAT;
	std::string functionName = "";
	std::string BlockType = "";

	bool EnterFuncion = false;

	while (TokenManagment.GetSize() > TokenManagment.indexToken)
	{
		target = TokenManagment.NextToken();
		switch (target.ID)
		{
		case IDToken::ID:
		{
			Assign(target, Context, functionName);
		}
			break;
		case IDToken::KEYWORD:
		{
			if (target.Desc == "var")
			{
				target = TokenManagment.NextToken();
				Var(target, Context, functionName);
			}
			else if (target.Desc == "procedure" && functionName == "")
			{
				//Procedimiento
				BlockType = "procedure";
				Context = Category::Param;
				std::string name;
				

				target = TokenManagment.NextToken();

				if (target.ID == IDToken::ID)
				{
					name = target.Desc;
					target = TokenManagment.NextToken();
					SymboolManager.AddVar(target, name, "", Category::Process, Type::INDEF, 0, nullptr, nullptr);
					functionName = name;
				}
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se espetaba un ID");


				//Parametros
				if (target.Desc == "(")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se espetaba un (");

				int limit = 10;
				while (target.Desc != ")" && limit > 0)
				{
					limit--;
					Var(target, Context, name);
					if(target.Desc != ")")
						target = TokenManagment.NextToken();
				}

				target = TokenManagment.NextToken();
				//Block
				Block(target, Context, functionName);
			}
			else if (target.Desc == "function" && functionName == "")
			{
				BlockType = "function";
				//Funcion
				Context = Category::Param;
				std::string name;

				target = TokenManagment.NextToken();

				if (target.ID == IDToken::ID)
				{
					name = target.Desc;
					target = TokenManagment.NextToken();	
				}
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se espetaba un ID");

				int first = TokenManagment.indexToken;

				while (target.Desc != ")")
				{
					target = TokenManagment.NextToken();
				}

				target = TokenManagment.NextToken();
				target = TokenManagment.NextToken();

				if (target.Desc == "float")
					type = Type::FLOAT;
				else if (target.Desc == "int")
					type = Type::INT;
				else if (target.Desc == "boolean")
					type = Type::BOOLEAN;
				else if (target.Desc == "string")
					type = Type::STRING;
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un tipo válido");

				SymboolManager.AddVar(target, name, "", Category::Function, type, 0, nullptr, nullptr);

				TokenManagment.indexToken = first - 1;
				target = TokenManagment.NextToken();


				//Parametros
				if (target.Desc == "(")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se espetaba un (");


				while (target.Desc != ")")
				{
					Var(target, Context, name);
					if (target.Desc != ")")
						target = TokenManagment.NextToken();
				}

				target = TokenManagment.NextToken();

				if (target.Desc == ":")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un :");

				if (target.ID == IDToken::KEYWORD)
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un tipo válido");

				//Block
				functionName = name;
				Block(target, Context, functionName);

			}
			else if (target.Desc == "return")
			{
				if (BlockType == "procedure" || BlockType == "main")
				{
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, BlockType + "no debe tener retorno");
					TokenManagment.PanicMode(";");
				}
				else {
					target = TokenManagment.NextToken();
					Type::E t;
					if (target.ID == IDToken::FLOAT)
						t = Type::FLOAT;
					else if (target.ID == IDToken::INT)
						t = Type::INT;
					else
						ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un tipo compatible");
					if (t != type)
						ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "el tipo de retorno no es el mismo");
					target = TokenManagment.NextToken();
					if (target.Desc != ";")
						ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un ;");
				}
			}
			else if (target.Desc == "main")
			{
				BlockType = "main";
				std::string name = "main";
				target = TokenManagment.NextToken();
				target = TokenManagment.NextToken();
				target = TokenManagment.NextToken();

				functionName = name;
				//Block
				Block(target, Context, functionName);
			}
			else if (target.Desc == "while" && functionName != "")
			{
				EnterFuncion = true;
				std::string name = functionName;

				target = TokenManagment.NextToken();

				//Expresion
				TypeManager.AddElement(Expresion(target, Context, name, Type::BOOLEAN), Type::BOOLEAN, target.nLine);
				//Block
				Block(target, Context, name);
			}
			else if (target.Desc == "for" && functionName != "")
			{
				target = TokenManagment.NextToken();
				if (target.Desc == "(")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", "se esperaba un (", target.Desc);

				// Assig
				Assign(target, Context, functionName);

				if (target.Desc == ";")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", "se esperaba un ;", target.Desc);

				// Expresion
				TypeManager.AddElement(Expresion(target, Context, functionName, Type::BOOLEAN), Type::BOOLEAN, target.nLine);
				//Expresion(target, Context, functionName);

				// Expresion
				Expresion(target, Context, functionName, Type::BOOLEAN);

				//Block
				Block(target, Context, functionName);


			}
			else if (target.Desc == "if")
			{
				EnterFuncion = true;
				target = TokenManagment.NextToken();
				
				//Expresion
				TypeManager.AddElement(Expresion(target, Context, functionName, Type::BOOLEAN), Type::BOOLEAN, target.nLine);
				//Expresion(target, Context, functionName);
				
				//Block
				Block(target, Context, functionName);

			}
			else if (target.Desc == "switch")
			{
				EnterFuncion = true;
				target = TokenManagment.NextToken();
				
				int inicio = TokenManagment.indexToken;

				if (target.Desc == "(")
					target = TokenManagment.NextToken();
				else {
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un (");
					target = TokenManagment.NextToken();
				}

				if (target.ID == IDToken::INT || target.ID == IDToken::ID)
				{
					TokenManagment.indexToken = inicio - 1;
					target = TokenManagment.NextToken();
					TypeManager.AddElement(Expresion(target, Context, functionName, Type::INT), Type::INT, target.nLine);
					//Expresion(target, Context, functionName);
				}
				else {
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un int");
					target = TokenManagment.NextToken();
				}

				if (target.Desc == ")")
					target = TokenManagment.NextToken();
				else if(target.Desc == "{")
					Block(target, Context, functionName);
				else {
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un )");
					target = TokenManagment.NextToken();
				}

				

			}
			else
			{
				ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "este elemento no es ninguno de los que se esperan");
			}
		}
			break;
		case IDToken::INT:
		{
			target = TokenManagment.NextToken();

			if (target.Desc == ":")
				target = TokenManagment.NextToken();
			else if (target.Desc == ";" || target.ID == IDToken::DELIMITER)
			{
				ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "este elemento no es ninguno de los que se esperan");
				target = TokenManagment.NextToken();
			}

			Block(target, Context, functionName);
		}
			break;
		case IDToken::FLOAT:
		{
			Token ID = target;
			target = TokenManagment.NextToken();

			if (target.Desc == ";" || target.ID == IDToken::DELIMITER)
			{
				ErrorManagment.AddError(ID.nLine, "<sint>", ID.Desc, "se esperaba un int");
				target = TokenManagment.NextToken();
			}

			Block(target, Context, functionName);
		}
			break;
		case IDToken::DELIMITER:
			break;
		case IDToken::RELATIONSHIP_OP:
			break;
		case IDToken::ASSIGNATION:
			break;
		case IDToken::ARITMETIC_OP:
			break;
		case IDToken::O_AGRUP_OP:
			break;
		case IDToken::C_AGRUP_OP:
		{
			if (!EnterFuncion)
			{
				Context = Category::Global;
				functionName = "";
			}
			EnterFuncion = false;
		}
			break;
		case IDToken::LOGICAL_OP:
			break;
		case IDToken::CONST_AF:
			break;
		default:
			break;
		}
	}

	SymboolManager.Save();
	SemanticAnalisis();
}

void FSM::SemanticAnalisis()
{
	TypeManager.SetSymbolManager(&SymboolManager);
	TypeManager.SetErrorControler(&ErrorManagment);
	/*for (auto it = TypeManager.Elements.begin(); it != TypeManager.Elements.end(); it++)
	{
		std::unordered_map<std::string, std::vector<Token>>::const_iterator expr = TypeManager.Expresions.find(it->first);
		int indexSub = 0;
		if (expr != TypeManager.Expresions.end())
		{
			std::unordered_map<std::string, SubExpr>::const_iterator subExp = TypeManager.SubExpresions.find(expr->second[indexSub++].Desc);
			if (subExp != TypeManager.SubExpresions.end())
			{
				for (auto term : subExp->second.Expr)
				{
					if (term.ID == IDToken::ID)
					{
						int b = *(int*)(TypeManager.GenerateValueExpr(subExp->second));
						int g = b;

					}
				}
			}
		}
	}*/

	// Check subExpresions
	TypeManager.CheckSubExp();
	TypeManager.CheckExpresions();
	// Debo checar asignaciones
	TypeManager.CheckAssign();
	// 
	TypeManager.CheckDimensions();
	//
	TypeManager.CheckTypes();
	
}

Descriptores::E FSM::CheckDescriptor(char character)
{
	switch (character)
	{
	case 'a':
	case 'b':
	case 'c':
	case 'd':
	case 'e':
	case 'f':
	case 'g':
	case 'h':
	case 'i':
	case 'j':
	case 'k':
	case 'l':
	case 'm':
	case 'n':
	case 'o':
	case 'p':
	case 'q':
	case 'r':
	case 's':
	case 't':
	case 'u':
	case 'v':
	case 'w':
	case 'x':
	case 'y':
	case 'z':
	case 'A':
	case 'B':
	case 'C':
	case 'D':
	case 'E':
	case 'F':
	case 'G':
	case 'H':
	case 'I':
	case 'J':
	case 'K':
	case 'L':
	case 'M':
	case 'N':
	case 'O':
	case 'P':
	case 'Q':
	case 'R':
	case 'S':
	case 'T':
	case 'U':
	case 'V':
	case 'W':
	case 'X':
	case 'Y':
	case 'Z':
		return Descriptores::Letter;

	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		return Descriptores::Digit;

	case '_':
		return Descriptores::Underscore;

	case ',':
		return Descriptores::Comma;

	case ':':
		return Descriptores::TwoPoints;

	case ';':
		return Descriptores::Semicolon;

	case '.':
		return Descriptores::Point;

	case ' ':
	case '	':
		return Descriptores::Space;

	case '\n':
		return Descriptores::EndLine;

	case '=':
		return Descriptores::Equal;

	case '+':
		return Descriptores::Plus;

	case '-':
		return Descriptores::Less;

	case '*':
		return Descriptores::Mul;

	case '/':
		return Descriptores::Divide;

	case '%':
		return Descriptores::Module;

	case '^':
		return Descriptores::Exp;
	
	case '(':
		return Descriptores::Op_P;

	case ')':
		return Descriptores::Cl_P;

	case '{':
		return Descriptores::Op_Key;

	case '}':
		return Descriptores::Cl_Key;

	case '[':
		return Descriptores::Op_Brack;

	case ']':
		return Descriptores::Cl_Brack; 

	case '<':
		return Descriptores::LessThan;

	case '>':
		return Descriptores::GreaterThan;

	case '!':
		return Descriptores::Exclamation;

	case '&':
		return Descriptores::Ampersand;

	case '|':
		return Descriptores::Or;

	case '"':
		return Descriptores::Const_Af;
	
	default:
		return Descriptores::Undef;

	}

	return Descriptores::E();
}

bool FSM::Save(std::string file_name)
{
	std::ofstream myfile;

	myfile.open(file_name + ".txt", std::ios::out);
	if (myfile.is_open())
	{
		myfile << m_formatString;
		myfile.close();
	}
	else
		return true;
}

bool FSM::Load(std::string file_name)
{
	std::ifstream myfile;

	myfile.open(file_name + ".txt", std::ios::in);
	if (myfile.fail())
	{
		printf("\nErro al cargar el archivo\n");
		return false;
	}
	while (!myfile.eof()) {
		std::string s;
		std::getline(myfile, s);
		m_formatString += s + '\n';
	}

	myfile.close();

	return true;
}

void FSM::Var(Token &target, Category::E Context, std::string FunctionName)
{
	Type::E type;
	int firstPoint = TokenManagment.indexToken - 1;

	int lastPoint = 0;

	int limit = 20;
	while (target.Desc != ";" && target.Desc != ")" && limit > 0)
	{
		limit--;
		lastPoint = TokenManagment.indexToken;
		target = TokenManagment.NextToken();
	}

	lastPoint--;
	target = TokenManagment.GetToken(lastPoint);
	if (target.Desc == "float")
		type = Type::FLOAT;
	else if (target.Desc == "int")
		type = Type::INT;
	else if (target.Desc == "string")
		type = Type::STRING;
	else if (target.Desc == "boolean" || target.Desc == "bool")
		type = Type::BOOLEAN;
	else {
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un tipo");
		type = Type::INDEF;
		target = TokenManagment.PanicMode(";)");
	}

	if (type != Type::INDEF)
	{
		target = TokenManagment.GetToken(firstPoint);
		TokenManagment.indexToken = firstPoint + 1;

		int limit = 20;
		while (target.Desc != ":" && target.Desc != ";" && target.Desc != ")" && limit > 0)
		{
			limit--;
			if (target.ID == IDToken::ID)
			{
				std::string name;
				int dimension = 0;

				name = target.Desc;

				target = TokenManagment.NextToken();

				if (target.Desc == "," || target.Desc == ":")
				{
					SymboolManager.AddVar(target, name, FunctionName, Context, type, 0, NULL, NULL);
					if (target.Desc == ")")
						return;
				}
				else if (Context == Category::Global || Context == Category::Process || Context == Category::Function)
				{
					if (target.Desc == "[")
						target = TokenManagment.NextToken();
					else
						ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Elemento no identificado");

					if (target.ID == IDToken::INT)
					{
						dimension = atoi(target.Desc.c_str());
						target = TokenManagment.NextToken();
					}
					else
						ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Dimension no valida");

					if (target.Desc == "]")
						target = TokenManagment.NextToken();
					else
						ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Debes cerrar el corchete");

					SymboolManager.AddVar(target, name, FunctionName, Context, type, dimension, NULL, NULL);

				}
				else
				{
					Token a, b, c;
					a = target;
					target = TokenManagment.NextToken();
					b = target;
					target = TokenManagment.NextToken();
					c = target;
					target = TokenManagment.NextToken();

					if (a.Desc == "[" || b.ID == Type::INT || c.Desc == "]")
					{
						ErrorManagment.AddError(target.nLine, "<sint>", TokenManagment.GetToken(TokenManagment.indexToken - 5).Desc, "los parámetros no pueden tener dimension");
						target = TokenManagment.PanicMode(";");
						return;
					}
					else
						TokenManagment.indexToken -= 2;
				}

			}
			else if (target.Desc == ",")
			{
				ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un ID");
			}

			target = TokenManagment.NextToken();
		}
	}
}

std::string FSM::Expresion(Token & target, Category::E Context, std::string FunctionName, Type::E type)
{
	if (target.ID != IDToken::ID || target.ID != IDToken::INT || target.ID != IDToken::FLOAT || target.nLine != IDToken::LOGICAL_OP)
	{
		TokenManagment.indexToken -= 1;
	}
	else
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba una expresion");

	std::vector<Token> Expresion;
	int limit = 20;
	while (target.Desc != "{" && target.ID != IDToken::DELIMITER && target.ID != IDToken::ASSIGNATION && limit > 0)
	{
		target = TokenManagment.NextToken();
		limit--;
		Expresion.push_back(target);
	}

	static int nSubExpr;
	std::vector<Token> Expr;
	bool exit = false;
	/*bool b_expr = false;*/

	while (!exit)
	{
		SubExpr sub;
		sub.ID = "subExp";
		sub.ID += std::to_string(nSubExpr);

		int ptrInit = 0;
		int ptrFin = 0;

		exit = true;
		for (int i = 0; i < Expresion.size(); i++)
		{
			if (Expresion[i].Desc == "(" || Expresion[i].Desc == "[")
			{
				exit = false;
				ptrInit = i;
				/*if(Expresion[i].Desc == "[")
					b_expr = true;*/

			}


			if (Expresion[i].Desc == ")" || Expresion[i].Desc == "]")
			{
				ptrFin = i;
				break;
			}
		}

		if (exit)
			break;

		for (int i = ptrInit; i < ptrFin + 1; i++)
		{
			if (Expresion[i].Desc != "(" && Expresion[i].Desc != ")" && Expresion[i].Desc != "[" && Expresion[i].Desc != "]")
			{
				sub.Expr.push_back(Expresion[i]);
				sub.varType = type;
				sub.nLine = Expresion[i].nLine;
			}
			Expresion[i].Desc = "1z2x3c";
		}
		/*for (auto &t : Expresion)
		{		
			if (t.Desc == ")" || t.Desc == ";")
			{
				t.Desc = "1z2x3c";
				break;
			}
			else if (t.Desc == "(")
			{
				for (auto &t2 : Expresion)
				{
					if (t2.Desc == "1z2x3c")
						t2.Desc = "(";
				}
				sub.Expr.clear();
			}
			else
				sub.Expr.push_back(t);
			t.Desc = "1z2x3c";
		}*/

		std::vector<Token> auxExpr;
		bool inserted = false;
		for (auto &t : Expresion)
		{
			if (t.Desc == "1z2x3c" && !inserted)
			{
				Token tok;
				tok.Desc = sub.ID;
				tok.nLine = t.nLine;
				//tok.Type = t.Type;
				auxExpr.push_back(tok);
				auxExpr.back().nLine = t.nLine;
				
				inserted = true;
			} else if (t.Desc != "1z2x3c")
				auxExpr.push_back(t);
		}
		Expresion.clear();
		Expresion = auxExpr;

		Token auxT;
		auxT.Desc = sub.ID;
		auxT.nLine = sub.nLine;
		//auxT.Type = sub.varType;
		Expr.push_back(auxT);
		//SubExpresions.insert({ { sub.ID, sub } });
		TypeManager.AddSubExp(sub.ID, sub);
		nSubExpr++;
	}

	static int nExpresions;
	std::string expr = "expr";
	expr += std::to_string(nExpresions++);
	//Expresions.insert({ { expr, Expresion} });
	TypeManager.AddExp(expr, Expresion);
	//if (b_expr) {
	//	//Token a;
	//	//a = TokenManagment.GetToken(ptrInit - 1);
	//	TypeManager.AddDimensionTest("A", expr, Context);
	//}
	return expr;
	/*std::vector<Token> aux;
	int exit = 1;
	while (exit > 0)
	{
		if (target.Desc == "(")
		{
			exit++;
			target = TokenManagment.NextToken();
		}
		else if (target.Desc == ")")
		{
			exit--;
		}
		else if (target.Desc == "{")
		{
			if(exit > 1)
				ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un )");
			exit = 0;
			TokenManagment.indexToken -= 1;
			break;
		}
		target = TokenManagment.NextToken();
		if (target.Desc != ")" && target.ID != IDToken::DELIMITER
			&& target.ID != IDToken::O_AGRUP_OP
			&& target.ID != IDToken::C_AGRUP_OP)
			aux.push_back(target);
	}

	if (aux.size() >= 3)
	{
		for (int a = 0; a < aux.size() - 2; a += 2)
		{
			if (
				((aux[a].ID == IDToken::ID || aux[a].ID == IDToken::INT || aux[a].ID == IDToken::FLOAT)
				&& aux[a + 1].ID == IDToken::RELATIONSHIP_OP
				&& (aux[a + 2].ID == IDToken::ID || aux[a + 2].ID == IDToken::INT || aux[a + 2].ID == IDToken::FLOAT))

				|| ((aux[a].ID == IDToken::ID || aux[a].ID == IDToken::INT || aux[a].ID == IDToken::FLOAT)
					&& aux[a + 1].ID == IDToken::ARITMETIC_OP
					&& (aux[a + 2].ID == IDToken::ID || aux[a + 2].ID == IDToken::INT || aux[a + 2].ID == IDToken::FLOAT))
				
				|| (aux[a].ID == IDToken::ID
					&& aux[a + 1].ID == IDToken::ARITMETIC_OP
					&& aux[a + 2].ID == IDToken::ARITMETIC_OP)
				
				|| (aux[a].ID == IDToken::ID
					&& aux[a + 1].ID == IDToken::LOGICAL_OP
					&& aux[a + 2].ID == IDToken::ID))
			{

			}
			else
				ErrorManagment.AddError(target.nLine, "<sint>", aux[a].Desc, "Expresion no válida");

		}
	}
	else if (aux.size() == 2)
	{
		if (aux[0].ID == IDToken::LOGICAL_OP)
		{
		}
		else
			ErrorManagment.AddError(target.nLine, "<sint>",aux[0].Desc, "Expresion no válida");
	}
	else if (aux.size() == 1)
	{
		if (aux[0].ID == IDToken::ID)
		{
		}
		else
		{
			ErrorManagment.AddError(target.nLine, "<sint>", aux[0].Desc, "Expresion no válida");
		}

	}
	else {
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Expresion no válida");
		TokenManagment.indexToken -= 1;
		target = TokenManagment.PanicMode(")");
	}

	if(target.Desc != "{")
		target = TokenManagment.NextToken();*/
}

void FSM::Block(Token & target, Category::E & Context, std::string FuctionName)
{
	if (target.Desc != "{")
	{
		ErrorManagment.AddError(target.nLine, "<sint>", "se esperaba un {", target.Desc);
		target = TokenManagment.NextToken();
		if (target.ID == IDToken::KEYWORD)
		{
			Context = Category::Local;
			TokenManagment.indexToken -= 2;
		}

	}
	else if (target.Desc == "{" || target.ID == IDToken::KEYWORD)
	{
		Context = Category::Local;
	}
	else
	{
		TokenManagment.PanicMode("}");
	}
}

void FSM::Assign(Token & target, Category::E & Context, std::string FuctionName)
{
	Type::E tipo = Type::INDEF;
	Token ID = target;
	if (target.ID == IDToken::ID)
	{
		tipo = GetTypeByIDToken(target);

		target = TokenManagment.NextToken();
	}
	else
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "se esperaba un ID");

	bool dimen = false;
	
	if(SymboolManager.FindElement(ID.Desc) == NULL)
		ErrorManagment.AddError(ID.nLine, "<sint>", ID.Desc, "variable no definida");

	if (target.ID == IDToken::ASSIGNATION)
		target = TokenManagment.NextToken();
	else if (target.Desc == ":")
	{
		ErrorManagment.AddError(ID.nLine, "<sint>", ID.Desc, "se esperaba un int");
		target = TokenManagment.NextToken();
	}
	else if (target.Desc == "[")
	{
		TypeManager.AddDimensionTest(ID.Desc, Expresion(target, Context, FuctionName, Type::INT), Context);
		if (SymboolManager.FindElement(ID.Desc)->m_iDimension == 0)
			ErrorManagment.AddError(ID.nLine, "<sint>", ID.Desc, "la variable no es un arreglo");
		target = TokenManagment.NextToken();
		dimen = true;
		/*int dimen = SymboolManager.FindElement(ID.Desc)->m_iDimension;
		if (dimen != 0)
		{
			target = TokenManagment.NextToken();
			if (atoi(target.Desc.c_str()) >= 0 && atoi(target.Desc.c_str()) <= dimen)
			{
				target = TokenManagment.NextToken();
				target = TokenManagment.NextToken();
			}
			else
				ErrorManagment.AddError(ID.nLine, "<sint>", ID.Desc, ID.Desc + " fuera de rango");
		} 
		else
		{
			ErrorManagment.AddError(ID.nLine, "<sint>", ID.Desc, ID.Desc + " no es un arreglo");
			target = TokenManagment.NextToken();
			target = TokenManagment.NextToken();
			target = TokenManagment.NextToken();
		}*/
	}
	else
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un =");

	if (SymboolManager.FindElement(ID.Desc) != NULL)
	{
		if (SymboolManager.FindElement(ID.Desc)->m_iDimension > 0 && !dimen)
			ErrorManagment.AddError(ID.nLine, "<sint>", ID.Desc, "la variable es un arreglo");
	}
	
	std::string expr = Expresion(target, Context, FuctionName, tipo);
	TypeManager.AddElement(expr, tipo, ID.nLine);
	TypeManager.AddAssignation(ID.Desc, expr);

	/*CGlobalNode *var = SymboolManager.FindElement(ID.Desc);
	if (var == NULL)
		ErrorManagment.AddError(ID.nLine, "<sint>", ID.Desc, "variable indefinida");*/
	
}

Type::E FSM::GetTypeByIDToken(Token target)
{
	CGlobalNode *node = SymboolManager.FindElement(target.Desc);
	if (node != nullptr)
	{
		return node->m_type;
	}
	else
		return Type::INDEF;

	/*if (target.Type == "float")
		return Type::FLOAT;
	else if (target.Type == "int")
		return Type::INT;
	else if (target.Type == "string")
		return Type::STRING;
	else if (target.Type == "bool" || target.Type == "boolean")
		return Type::BOOLEAN;*/
}

void FSM::Clean()
{
	ErrorManagment.Clean();
	TokenManagment.Clean();
}


