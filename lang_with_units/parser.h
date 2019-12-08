#pragma once

#include "lexer.h"

class Parser 
{
	Lexer& lexer;

public:
	Parser(Lexer& lex);
	void lexAnalysis();
};