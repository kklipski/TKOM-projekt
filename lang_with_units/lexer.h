#pragma once

#include "source.h"
#include <string>

enum Token	// language with units' lexical atoms 
{
	defSym, varSym, whileSym, printSym, ifSym, elseSym, returnSym, // keywords

	NKEYS, MAXKEY = returnSym,

	id, num, charStr, unit, semicolon, lRoundBr, rRoundBr, lCurlyBr, rCurlyBr, 
	assignOp, comma, orOp, andOp, eqToOp, notEqToOp, grThanOp, grThanOrEqToOp, 
	lessThanOp, lessThanOrEqToOp, plus, minus, times, divOp, notOp, others, eof
};

enum ScanErrors { ID_TOO_LONG = 1, NUM_VAL_SIZE_EXCEEDED, UNIT_NOT_DEFINED };

class Lexer
{
	struct KeyRec	// keyword descriptor
	{
		Token atom;
		std::string keyword;
	};

	TextPos atomPos;	// atom's position in source file
	int c; // current char
	std::string chStr;	// variable to store char string being created by lexer
	std::string ident;	// variable to store identificator being created by lexer
	static KeyRec keyTab[NKEYS];
	int number;	// variable to store number being created by lexer
	std::string un;	// variable to store unit being created by lexer
	Source& source;
	static const char* units[12];

	void nextChar();

public:
	Lexer(Source& src);
	const std::string& getChStr();
	const std::string& getIdent();
	const std::string& getUn();
	int getNumber();
	Token nextSymbol();	// returns next lexical atom
	void scanError(int errCode, const char* genMsg = "", const char* addMsg = "");
};