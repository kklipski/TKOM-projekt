#include <vector>
#include "Lexer.h"

const Lexer::KeywordDescriptor Lexer::keywordTable[to_underlying(Token::NUMBER_OF_KEYWORDS)] =
{
	// keyword				atom
	//-----------------------------------
	 { Token::defSymbol,	"def"		},
	 { Token::varSymbol,	"var"		},
	 { Token::whileSymbol,	"while"		},
	 { Token::printSymbol,	"print"		},
	 { Token::ifSymbol,		"if"		},
	 { Token::elseSymbol,	"else"		},
	 { Token::returnSymbol,	"return"	}
};

const std::array<std::string, 12> Lexer::units = { "m", "kg", "s", "Hz", "N", "J", "W", "m/s",
	"m/s^2", "N*s", "J*s", "kg*m^2" };

void Lexer::error(int errorCode, const TextPosition& position, const std::string& generalMessage,
	const std::string& additionalMessage)
{
	/* char array for storing line with error (max maxNumberOfCharacters returned by
	getline() */
	char errorLine[maxNumberOfCharacters + 1];
	int currentPosition = inputFileStream->tellg();
	// move to the beginning of the line (column numeration starts with 1)
	inputFileStream->seekg(currentPosition - textPosition.columnNumber + 1);
	inputFileStream->getline(errorLine, maxNumberOfCharacters + 1);
	inputFileStream->seekg(currentPosition);	// return to initial position
	throw std::runtime_error("(Line: " + std::to_string(textPosition.lineNumber) + ", column: "
		+ std::to_string(textPosition.columnNumber) + ") ERROR " + std::to_string(errorCode) + ": "
		+ generalMessage + additionalMessage + "\n\t" + errorLine + "\n\n");
}

void Lexer::incrementLine()
{
	textPosition.lineNumber++;
	textPosition.columnNumber = 1;
}

void Lexer::nextChar()
{ 
	textPosition.columnNumber++;
	character = inputFileStream->get();
}

int Lexer::processAmbiguousOperators(Token* returnedToken)
{
	switch (character)
	{
	case '=':
		nextChar();

		if (character == '=')
		{
			nextChar();
			*returnedToken = Token::equalToOperator;
			return 1;
		}

		*returnedToken = Token::assignmentOperator;
		return 1;

	case '!':
		nextChar();

		if (character == '=')
		{
			nextChar();
			*returnedToken = Token::notEqualToOperator;
			return 1;
		}

		*returnedToken = Token::notOperator;
		return 1;

	case '>':
		nextChar();

		if (character == '=')
		{
			nextChar();
			*returnedToken = Token::greaterThanOrEqualToOperator;
			return 1;
		}

		*returnedToken = Token::greaterThanOperator;
		return 1;

	case '<':
		nextChar();

		if (character == '=')
		{
			nextChar();
			*returnedToken = Token::lessThanOrEqualToOperator;
			return 1;
		}

		*returnedToken = Token::lessThanOperator;
		return 1;

	default:
		return 0;
	}
}

int Lexer::processCharString(Token* returnedToken)
{
	if (character == '"')
	{
		constructedString.clear();
		nextChar();

		do
		{
			constructedString.push_back(character);
			nextChar();
		} while (character != '"' && character != EOF);

		if (character == EOF)
		{
			*returnedToken = Token::others;
			return 1;
		}

		*returnedToken = Token::charStringAtom;
		nextChar();
		return 1;
	}

	else return 0;
}

int Lexer::processIdOrKeyword(Token* returnedToken)
{
	if (isalpha(character) || character == '_')
	{
		constructedString.clear();
		int idLength = 0;
		bool idTooLong = 0;

		do
		{
			if (character == '_')
			{
				do {
					idLength++;
					idTooLong = idTooLong || idLength > 31;
					constructedString.push_back(character);
					nextChar();
				} while (isalnum(character) || character == '_');

				serveIdTooLong(idTooLong);
				*returnedToken = Token::idAtom;
				return 1;
			}

			else
			{
				idLength++;
				idTooLong = idTooLong || idLength > 31;
				constructedString.push_back(character);
				nextChar();
			}
		} while (isalnum(character) || character == '_');

		if (testIfKeyword(returnedToken)) return 1;

		serveIdTooLong(idTooLong);
		*returnedToken = Token::idAtom;
		return 1;
	}

	else return 0;
}

int Lexer::processNumber()
{
	if (isdigit(character))
	{
		unsigned long long number = 0;
		bool sizeExceeded = false;

		do
		{
			number = number * 10 + (character - '0');
			sizeExceeded = sizeExceeded || number > INT32_MAX;
			nextChar();
		} while (isdigit(character));

		if (sizeExceeded) error(to_underlying(ScanErrors::NUMERIC_VALUE_SIZE_EXCEEDED),
			atomPosition, "Numeric value exceeds the size limit!");

		constructedNumber = (int)number;
		return 1;
	}

	else return 0;
}

void Lexer::processOneCharOperators(Token* returnedToken)
{
	switch (character)
	{
	case ';':
		nextChar();
		*returnedToken = Token::semicolon;
		break;

	case '(':
		nextChar();
		*returnedToken = Token::leftRoundBracket;
		break;

	case ')':
		nextChar();
		*returnedToken = Token::rightRoundBracket;
		break;

	case '{':
		nextChar();
		*returnedToken = Token::leftCurlyBracket;
		break;

	case '}':
		nextChar();
		*returnedToken = Token::rightCurlyBracket;
		break;

	case ',':
		nextChar();
		*returnedToken = Token::comma;
		break;

	case '|':
		nextChar();
		*returnedToken = Token::orOperator;
		break;

	case '&':
		nextChar();
		*returnedToken = Token::andOperator;
		break;

	case '+':
		nextChar();
		*returnedToken = Token::plus;
		break;

	case '-':
		nextChar();
		*returnedToken = Token::minus;
		break;

	case '*':
		nextChar();
		*returnedToken = Token::times;
		break;

	case '/':
		nextChar();
		*returnedToken = Token::divisionOperator;
		break;

	// illegal chars
	default:
		nextChar();
		*returnedToken = Token::others;
		break;
	}
}

int Lexer::processUnit(Token* returnedToken)
{
	if (character == '[')
	{
		constructedString.clear();
		nextChar();

		do
		{
			constructedString.push_back(character);
			nextChar();
		} while (character != ']' && character != EOF);

		if (character == EOF)
		{
			*returnedToken = Token::others;
			return 1;
		}

		nextChar();

		for (int i = 0; i < 12; i++)
		{
			if (constructedString == units[i])
			{
				*returnedToken = Token::unitAtom;
				recognizedUnit = (Unit)i;
				return 1;
			}
		}

		error(to_underlying(ScanErrors::UNIT_NOT_DEFINED), atomPosition, "Unit not defined: ",
			constructedString.c_str());
		*returnedToken = Token::others;
		return 1;
	}

	else return 0;
}

void Lexer::serveIdTooLong(const bool& idTooLong)
{
	if (idTooLong)
	{
		error(to_underlying(ScanErrors::ID_TOO_LONG), atomPosition, "Identifier too long!");
		constructedString = constructedString.substr(0, maxIdLength);

	}
}

void Lexer::setAtomPosition()
{
	// we want a start position of atom, that's why 'textPosition.columnNumber - 1' is used
	atomPosition.lineNumber = textPosition.lineNumber;
	atomPosition.columnNumber = textPosition.columnNumber - 1;
}

int Lexer::skipWhitespaces()
{
	do
	{
		// skip whitespaces except '\n'
		while (character == ' ' || character == '\t' || character == '\v' || character == '\f' ||
			character == '\r') nextChar();

		if (character == EOF) return 1;

		if (character == '\n')
		{
			incrementLine();
			nextChar();
		}
	} while (isspace(character) || character == EOF);

	return 0;
}

int Lexer::testIfKeyword(Token* returnedToken)
{
	for (int i = 0; i < to_underlying(Token::NUMBER_OF_KEYWORDS); i++)
	{
		if (keywordTable[i].keyword == constructedString)
		{
			*returnedToken = keywordTable[i].atom;
			return 1;
		}
	}

	return 0;
}

Lexer::Lexer(std::istream* inputFile)
	:inputFileStream(inputFile)
{ 
	nextChar();
}

const std::string& Lexer::getConstructedString()
{
	return constructedString;
}

int Lexer::getConstructedNumber()
{ 
	return constructedNumber; 
}

Unit Lexer::getRecognizedUnit()
{
	return recognizedUnit;
}

Token Lexer::nextSymbol()
{
	Token returnedToken;

	if (skipWhitespaces()) return Token::endOfFile;

	setAtomPosition();	// token is expected

	if (processIdOrKeyword(&returnedToken)) return returnedToken;

	else if (processNumber()) return Token::numberAtom;

	else if (processCharString(&returnedToken)) return returnedToken;

	else if (processUnit(&returnedToken)) return returnedToken;

	else if (processAmbiguousOperators(&returnedToken)) return returnedToken;

	else processOneCharOperators(&returnedToken);

	return returnedToken;
}

void Lexer::scanError(int errorCode, const std::string& generalMessage,
	const std::string& additionalMessage)
{
	error(errorCode, atomPosition, generalMessage, additionalMessage);
}