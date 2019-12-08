#include "parser.h"

int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		std::cout << "Filename not provided!" << std::endl;
		return 1;
	}

	Source src(argv[1]);
	Lexer lex(src);
	Parser par(lex);
	par.lexAnalysis();
	return 0;
}