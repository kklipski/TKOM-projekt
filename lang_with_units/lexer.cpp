#include "lexer.h"

Lexer::KeyRec Lexer::keyTab[NKEYS] =
{
	// keyword		atom
	//----------------------------
	 { defSym,		"def"		},
	 { varSym,		"var"		},
	 { whileSym,	"while"		},
	 { printSym,	"print"		},
	 { ifSym,		"if"		},
	 { elseSym,		"else"		},
	 { returnSym,	"return"	}
};

const char* Lexer::units[12] = {"m", "kg", "s", "Hz", "N", 
	"J", "W", "m/s", "m/s^2", "N*s", "J*s", "kg*m^2"};

void Lexer::nextChar() 
{ 
	c = source.nextChar(); 
}

Lexer::Lexer(Source& src):source(src)
{ 
	nextChar(); 
}

const std::string& Lexer::getChStr()
{
	return chStr;
}

const std::string& Lexer::getIdent() 
{ 
	return ident; 
}

const std::string& Lexer::getUn()
{
	return un;
}

int Lexer::getNumber() 
{ 
	return number; 
}

Token Lexer::nextSymbol()
{
	// whitespace / EOF
	do
	{
		// skip whitespaces except '\n'
		while (c == ' ' || c == '\t' || c == '\v' || c == '\f' || c == '\r') nextChar();

		if (c == EOF) return eof;

		if (c == '\n')
		{
			source.incLine();
			nextChar();
		}
	} while (isspace(c));

	atomPos = source.getPos();	// token is expected

	// id / keyword
	if (isalpha(c) || c == '_')
	{
		ident.clear();
		int idLength = 0;
		bool idTooLong = 0;

		do
		{
			if (c == '_')
			{
				do {
					idLength++;
					idTooLong = idTooLong || idLength > 31;
					ident.push_back(c);
					nextChar();
				} while (isalnum(c) || c == '_');

				return id;
			}

			else
			{
				idLength++;
				idTooLong = idTooLong || idLength > 31;
				ident.push_back(c);
				nextChar();
			}
		} while (isalnum(c) || c == '_');

		for (int i = 0; i < NKEYS; i++)
		{
			if (keyTab[i].keyword == ident) return keyTab[i].atom;
		}

		if (idTooLong)
		{
			scanError(ID_TOO_LONG, "Identifier too long!");
			ident = ident.substr(0, MAX_ID_LENGTH);
		}

		return id;
	}

	else
	{
		// number
		if (isdigit(c))
		{
			unsigned long long n = 0;
			bool sizeExceeded = false; 

			do
			{
				n = n * 10 + (c - '0');
				sizeExceeded = sizeExceeded || n > INT_MAX;
				nextChar();
			} while (isdigit(c));

			if (sizeExceeded) scanError(NUM_VAL_SIZE_EXCEEDED, 
				"Numeric value exceeds the size limit!");

			number = (int)n;
			return num;
		}

		else
		{
			// other atoms
			switch (c)
			{
			// char string
			case '"':
				chStr.clear();
				nextChar();

				do
				{
					chStr.push_back(c);
					nextChar();
				} while (c != '"');

				nextChar();
				return charStr;

			// unit
			case '[':
				un.clear();
				nextChar();

				do
				{
					un.push_back(c);
					nextChar();
				} while (c != ']');

				nextChar();

				for (int i = 0; i < 12; i++)
				{
					if (un == units[i]) return unit;
				}

				scanError(UNIT_NOT_DEFINED, "Unit not defined: ", un.c_str());
				return others;

			// operators starting with the same symbol
			case '=': 
				nextChar();

				if (c == '=') 
				{ 
					nextChar(); 
					return eqToOp; 
				}

				return assignOp;

			case '!': 
				nextChar();

				if (c == '=') 
				{
					nextChar(); 
					return notEqToOp; 
				}

				return notOp;

			case '>': 
				nextChar();

				if (c == '=') 
				{ 
					nextChar(); 
					return grThanOrEqToOp; 
				}

				return grThanOp;

			case '<': 
				nextChar();

				if (c == '=') 
				{ 
					nextChar(); 
					return lessThanOrEqToOp; 
				}

				return lessThanOp;

			// one-char operators
			case ';': 
				nextChar(); 
				return semicolon;

			case '(': 
				nextChar(); 
				return lRoundBr;

			case ')': 
				nextChar(); 
				return rRoundBr;

			case '{': 
				nextChar(); 
				return lCurlyBr;

			case '}': 
				nextChar(); 
				return rCurlyBr;

			case ',': 
				nextChar(); 
				return comma;

			case '|': 
				nextChar(); 
				return orOp;

			case '&': 
				nextChar(); 
				return andOp;

			case '+': 
				nextChar(); 
				return plus;

			case '-': 
				nextChar(); 
				return minus;

			case '*': 
				nextChar(); 
				return times;

			case '/': 
				nextChar(); 
				return divOp;

			// illegal chars
			default: 
				nextChar(); 
				return others;
			}
		}
	}
}

void Lexer::scanError(int errCode, const char* genMsg, const char* addMsg)
{
	source.error(errCode, atomPos, genMsg, addMsg);
}