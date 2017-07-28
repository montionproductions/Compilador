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
			ErrorManagment.AddError(nLine, "<Lex>", Token, "Expresion sin definicion");
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
				ErrorManagment.AddError(nLine, "<Lex>", "Indentificador no reconocido", Token + pts);
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
				ErrorManagment.AddError(nLine, "<Lex>", Token, "Expresion sin definicion");
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
				ErrorManagment.AddError(nLine, "<Lex>", "Se esperaba un float", Token);
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
				ErrorManagment.AddError(nLine, "<Lex>", "Se esperaba un operador logico", Token);

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
				ErrorManagment.AddError(nLine, "<Lex>", "Falto cerrar comillas", "\"");
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
		ErrorManagment.AddError(nLine, "<Lex>", "Comentario no cerrado al final del archivo", "/*");

	if(openConstAf)
		ErrorManagment.AddError(nLine, "<Lex>", "Falto cerrar comillas", "\"");

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
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se espetaba un ID");


				//Parametros
				if (target.Desc == "(")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se espetaba un (");

				
				while (target.Desc != ")")
				{
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
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se espetaba un ID");

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
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un tipo válido");

				SymboolManager.AddVar(target, name, "", Category::Function, type, 0, nullptr, nullptr);

				TokenManagment.indexToken = first - 1;
				target = TokenManagment.NextToken();


				//Parametros
				if (target.Desc == "(")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se espetaba un (");


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
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un :");

				if (target.ID == IDToken::KEYWORD)
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un tipo válido");

				//Block
				functionName = name;
				Block(target, Context, functionName);

			}
			else if (target.Desc == "return")
			{
				target = TokenManagment.NextToken();
				Type::E t;
				if (target.ID == IDToken::FLOAT)
					t = Type::FLOAT;
				else if (target.ID == IDToken::INT)
					t = Type::INT;
				else
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un tipo compatible");
				if(t != type)
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "El tipo de retorno no es el mismo");
				target = TokenManagment.NextToken();
				if (target.Desc != ";")
					ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un ;");
			}
			else if (target.Desc == "main")
			{
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
				Expresion(target, Context, name);
				//Block
				Block(target, Context, name);
			}
			else if (target.Desc == "for" && functionName != "")
			{
				target = TokenManagment.NextToken();
				if (target.Desc == "(")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", "Se esperaba un (", target.Desc);

				// Assig
				Assign(target, Context, functionName);

				if (target.Desc == ";")
					target = TokenManagment.NextToken();
				else
					ErrorManagment.AddError(target.nLine, "<sint>", "Se esperaba un ;", target.Desc);

				// Expresion
				Expresion(target, Context, functionName);

				// Expresion
				Expresion(target, Context, functionName);

				//Block
				Block(target, Context, functionName);


			}
			else if (target.Desc == "if")
			{
				EnterFuncion = true;
				target = TokenManagment.NextToken();
				
				//Expresion
				Expresion(target, Context, functionName);
				
				//Block
				Block(target, Context, functionName);

			}
			else
			{
				ErrorManagment.AddError(target.nLine, "<sint>", "Este elemento no es ninguno de los que se esperan", target.Desc);
			}
		}
			break;
		case IDToken::INT:
			break;
		case IDToken::FLOAT:
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

	while (target.Desc != ";" && target.Desc != ")")
	{
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
	else
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un tipo valido");

	target = TokenManagment.GetToken(firstPoint);
	TokenManagment.indexToken = firstPoint + 1;

	while (target.Desc != ":" && target.Desc != ";" && target.Desc != ")")
	{
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
					ErrorManagment.AddError(target.nLine, "<sint>", TokenManagment.GetToken(TokenManagment.indexToken - 5).Desc, "Los parámetros no pueden tener dimension");
					target = TokenManagment.PanicMode(";");
					return;
				}
				else
					TokenManagment.indexToken -= 2;
			}

		}

		target = TokenManagment.NextToken();
	}
}

void FSM::Expresion(Token & target, Category::E Context, std::string FunctionName)
{
	if (target.ID != IDToken::O_AGRUP_OP)
	{
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un (");
		target = TokenManagment.NextToken();
		//return;
	}

	if (target.ID != IDToken::ID || target.ID != IDToken::INT || target.ID != IDToken::FLOAT || target.nLine != IDToken::LOGICAL_OP)
	{
		TokenManagment.indexToken -= 1;
	}
	else
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba una expresion");


	std::vector<Token> aux;
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

	/*std::vector<Token> aux;
	while (target.Desc != ")" && target.Desc != ";")
	{
		target = TokenManagment.NextToken();
		if (target.Desc != ")" && target.Desc != "!" &&  target.Desc != ";")
			aux.push_back(target);
	}*/

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
		target = TokenManagment.NextToken();
}

void FSM::Block(Token & target, Category::E & Context, std::string FuctionName)
{
	if (target.Desc != "{")
	{
		ErrorManagment.AddError(target.nLine, "<sint>", "Se esperaba un {", target.Desc);
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
	if (target.ID == IDToken::ID)
		target = TokenManagment.NextToken();
	else
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un ID");

	if (target.ID == IDToken::ASSIGNATION)
		target = TokenManagment.NextToken();
	else
		ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un =");

	int count = 0;
	while (target.ID != IDToken::DELIMITER && count < 20 && target.ID != IDToken::C_AGRUP_OP)
	{
		count++;
		target = TokenManagment.NextToken();

		if (count == 20 || target.ID == IDToken::C_AGRUP_OP)
		{
			TokenManagment.indexToken -= 2;
			target = TokenManagment.NextToken();
			ErrorManagment.AddError(target.nLine, "<sint>", target.Desc, "Se esperaba un ;");
			return;
		}

	}	
}

void FSM::Clean()
{
	ErrorManagment.Clean();
	TokenManagment.Clean();
}


