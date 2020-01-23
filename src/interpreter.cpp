#include <fstream>
#include <iostream>
#include "parser/Parser.h"

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 2)
		{
			throw std::runtime_error("Wrong command!\n Proper command synopsis: "
				"./interpreter INPUT_FILENAME [>OUTPUT_FILENAME]\n");
		}

		std::unique_ptr<std::ifstream> inputFileStream(new std::ifstream(argv[1]));

		if (!inputFileStream)
		{
			const std::string msg = "Interpreter: FATAL ERROR - can't open input file: \"";
			throw std::runtime_error(msg + argv[1] + "\"\n");
		}
		
		Lexer lexer(inputFileStream.get());
		Parser parser(lexer);
		auto program(parser.program());
		inputFileStream->close();
		std::cout << program->execute() << std::endl; 
	}

	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return 1;
	}

	return 0;
}