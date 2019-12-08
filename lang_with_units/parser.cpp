#include "parser.h"

#include "parser.h"

Parser::Parser(Lexer & lex):lexer(lex)
{
	
}

void Parser::lexAnalysis()
{
	do
	{
		if (lexer.nextSymbol() == eof) break;
	} while (1);
}