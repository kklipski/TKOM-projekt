#pragma once

#include <array>
#include <istream>
#include <string>
#include "../commonElements.h"

enum class ScanErrors { ID_TOO_LONG = 1, NUMERIC_VALUE_SIZE_EXCEEDED, UNIT_NOT_DEFINED };

struct TextPosition	// struct for storing position in file
{
	int lineNumber;
	int columnNumber;

	TextPosition(int line = 1, int column = 1):lineNumber(line), columnNumber(column) {}
};

enum class Token	// language with units' lexsical atoms 
{
	defSymbol, varSymbol, whileSymbol, printSymbol, ifSymbol, elseSymbol, returnSymbol, // keywords

	NUMBER_OF_KEYWORDS, MAX_KEYWORD = returnSymbol,

	idAtom, numberAtom, charStringAtom, unitAtom, semicolon, leftRoundBracket, rightRoundBracket, 
	leftCurlyBracket, rightCurlyBracket, assignmentOperator, comma, orOperator, andOperator, 
	equalToOperator, notEqualToOperator, greaterThanOperator, greaterThanOrEqualToOperator, 
	lessThanOperator, lessThanOrEqualToOperator, plus, minus, times, divisionOperator, notOperator, 
	endOfFile, others, MAX_SYMBOL
};

class Lexer
{
	struct KeywordDescriptor
	{
		Token atom;
		std::string keyword;
	};

	TextPosition atomPosition;	// atom's position in source file
	int character; // current character
	int constructedNumber;	// variable to store number created by lexer
	std::string constructedString; // variable to store id, charString or unit created by lexer
	std::istream* inputFileStream;
	static const KeywordDescriptor keywordTable[to_underlying(Token::NUMBER_OF_KEYWORDS)];
	static const int maxIdLength = 31;
	/* how many characters from line with error will be printed when error is encountered */
	static const int maxNumberOfCharacters = 100;
	Unit recognizedUnit;
	TextPosition textPosition;	// position in source file (information for user)
	static const std::array<std::string, 12> units;

	void error(int errorCode, const TextPosition& position, const std::string& generalMessage = "",
		const std::string& additionalMessage = "");
	void incrementLine();
	void nextChar();
	int processAmbiguousOperators(Token* returnedToken);
	int processCharString(Token* returnedToken);
	int processIdOrKeyword(Token* returnedToken);
	int processNumber();
	void processOneCharOperators(Token* returnedToken);
	int processUnit(Token* returnedToken);
	void serveIdTooLong(const bool& idTooLong);
	void setAtomPosition();
	int skipWhitespaces();	// skips whitespaces and processes EOF
	int testIfKeyword(Token* returnedToken);

public:

	Lexer(std::istream* inputFile);
	const std::string& getConstructedString();
	int getConstructedNumber();
	Unit getRecognizedUnit();
	Token nextSymbol();	// returns next lexical atom
	void scanError(int errorCode, const std::string& generalMessage = "",
		const std::string& additionalMessage = "");
};