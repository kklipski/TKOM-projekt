#include "pch.h"

struct LexerTest : testing::Test {
	std::istringstream* iss;
	bool test;

	LexerTest() {
		iss = new std::istringstream();
	}
	~LexerTest() {
		delete iss;
	}
};

TEST_F(LexerTest, DefSymbolRecognizedProperly) {
	iss->str("def");
	Lexer lexer(iss);
	EXPECT_EQ(Token::defSymbol, lexer.nextSymbol());
}

TEST_F(LexerTest, VarSymbolRecognizedProperly) {
	iss->str("var");
	Lexer lexer(iss);
	EXPECT_EQ(Token::varSymbol, lexer.nextSymbol());
}

TEST_F(LexerTest, WhileSymbolRecognizedProperly) {
	iss->str("while");
	Lexer lexer(iss);
	EXPECT_EQ(Token::whileSymbol, lexer.nextSymbol());
}

TEST_F(LexerTest, PrintSymbolRecognizedProperly) {
	iss->str("print");
	Lexer lexer(iss);
	EXPECT_EQ(Token::printSymbol, lexer.nextSymbol());
}

TEST_F(LexerTest, IfSymbolRecognizedProperly) {
	iss->str("if");
	Lexer lexer(iss);
	EXPECT_EQ(Token::ifSymbol, lexer.nextSymbol());
}

TEST_F(LexerTest, ElseSymbolRecognizedProperly) {
	iss->str("else");
	Lexer lexer(iss);
	EXPECT_EQ(Token::elseSymbol, lexer.nextSymbol());
}

TEST_F(LexerTest, ReturnSymbolRecognizedProperly) {
	iss->str("return");
	Lexer lexer(iss);
	EXPECT_EQ(Token::returnSymbol, lexer.nextSymbol());
}

TEST_F(LexerTest,IdAtomRecognizedProperly) {
	iss->str("id");
	Lexer lexer(iss);
	EXPECT_EQ(Token::idAtom, lexer.nextSymbol());
	EXPECT_EQ("id", lexer.getConstructedString());
}

TEST_F(LexerTest, NumberAtomRecognizedProperly) {
	iss->str("2020");
	Lexer lexer(iss);
	EXPECT_EQ(Token::numberAtom, lexer.nextSymbol());
	EXPECT_EQ(2020, lexer.getConstructedNumber());
}

TEST_F(LexerTest, CharStringAtomRecognizedProperly) {
	iss->str("\"TKOM 19Z\"");
	Lexer lexer(iss);
	EXPECT_EQ(Token::charStringAtom, lexer.nextSymbol());
	EXPECT_EQ("TKOM 19Z", lexer.getConstructedString());
}

TEST_F(LexerTest, UnitAtomRecognizedProperly) {
	iss->str("[m]");
	Lexer lexer(iss);
	EXPECT_EQ(Token::unitAtom, lexer.nextSymbol());
	EXPECT_EQ(Unit::distance, lexer.getRecognizedUnit());
}

TEST_F(LexerTest, SemicolonRecognizedProperly) {
	iss->str(";");
	Lexer lexer(iss);
	EXPECT_EQ(Token::semicolon, lexer.nextSymbol());
}

TEST_F(LexerTest, LeftRoundBracketRecognizedProperly) {
	iss->str("(");
	Lexer lexer(iss);
	EXPECT_EQ(Token::leftRoundBracket, lexer.nextSymbol());
}

TEST_F(LexerTest, RightRoundBracketRecognizedProperly) {
	iss->str(")");
	Lexer lexer(iss);
	EXPECT_EQ(Token::rightRoundBracket, lexer.nextSymbol());
}

TEST_F(LexerTest, LeftCurlyBracketRecognizedProperly) {
	iss->str("{");
	Lexer lexer(iss);
	EXPECT_EQ(Token::leftCurlyBracket, lexer.nextSymbol());
}

TEST_F(LexerTest, RightCurlyBracketRecognizedProperly) {
	iss->str("}");
	Lexer lexer(iss);
	EXPECT_EQ(Token::rightCurlyBracket, lexer.nextSymbol());
}

TEST_F(LexerTest, AssignmentOperatorRecognizedProperly) {
	iss->str("=");
	Lexer lexer(iss);
	EXPECT_EQ(Token::assignmentOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, CommaRecognizedProperly) {
	iss->str(",");
	Lexer lexer(iss);
	EXPECT_EQ(Token::comma, lexer.nextSymbol());
}

TEST_F(LexerTest, OrOperatorRecognizedProperly) {
	iss->str("|");
	Lexer lexer(iss);
	EXPECT_EQ(Token::orOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, AndOperatorRecognizedProperly) {
	iss->str("&");
	Lexer lexer(iss);
	EXPECT_EQ(Token::andOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, EqualToOperatorRecognizedProperly) {
	iss->str("==");
	Lexer lexer(iss);
	EXPECT_EQ(Token::equalToOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, NotEqualToOperatorRecognizedProperly) {
	iss->str("!=");
	Lexer lexer(iss);
	EXPECT_EQ(Token::notEqualToOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, GreaterThanOperatorRecognizedProperly) {
	iss->str(">");
	Lexer lexer(iss);
	EXPECT_EQ(Token::greaterThanOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, GreaterThanOrEqualToOperatorRecognizedProperly) {
	iss->str(">=");
	Lexer lexer(iss);
	EXPECT_EQ(Token::greaterThanOrEqualToOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, LessThanOperatorRecognizedProperly) {
	iss->str("<");
	Lexer lexer(iss);
	EXPECT_EQ(Token::lessThanOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, LessThanOrEqualToOperatorRecognizedProperly) {
	iss->str("<=");
	Lexer lexer(iss);
	EXPECT_EQ(Token::lessThanOrEqualToOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, PlusRecognizedProperly) {
	iss->str("+");
	Lexer lexer(iss);
	EXPECT_EQ(Token::plus, lexer.nextSymbol());
}

TEST_F(LexerTest, MinusRecognizedProperly) {
	iss->str("-");
	Lexer lexer(iss);
	EXPECT_EQ(Token::minus, lexer.nextSymbol());
}

TEST_F(LexerTest, TimesRecognizedProperly) {
	iss->str("*");
	Lexer lexer(iss);
	EXPECT_EQ(Token::times, lexer.nextSymbol());
}

TEST_F(LexerTest, DivisionOperatorRecognizedProperly) {
	iss->str("/");
	Lexer lexer(iss);
	EXPECT_EQ(Token::divisionOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, NotOperatorRecognizedProperly) {
	iss->str("!");
	Lexer lexer(iss);
	EXPECT_EQ(Token::notOperator, lexer.nextSymbol());
}

TEST_F(LexerTest, EndOfFileRecognizedProperly) {
	iss->str("");
	Lexer lexer(iss);
	EXPECT_EQ(Token::endOfFile, lexer.nextSymbol());
}

TEST_F(LexerTest, OthersRecognizedProperly) {
	iss->str("@");
	Lexer lexer(iss);
	EXPECT_EQ(Token::others, lexer.nextSymbol());
}

TEST_F(LexerTest, IdTooLongErrorRaisedProperly) {
	test = false;

	try
	{
		iss->str("abcdefghijklmnopqrstuvwxyz_0123456789");
		Lexer lexer(iss);
		lexer.nextSymbol();
	}
	
	catch (const std::exception & e)
	{
		test = true;
	}

	EXPECT_TRUE(test);
}

TEST_F(LexerTest, NumericValueSizeExceededErrorRaisedProperly) {
	test = false;

	try
	{
		iss->str("123456789987654321");
		Lexer lexer(iss);
		lexer.nextSymbol();
	}

	catch (const std::exception & e)
	{
		test = true;
	}

	EXPECT_TRUE(test);
}

TEST_F(LexerTest, UnitNotDefinedErrorRaisedProperly) {
	test = false;

	try
	{
		iss->str("[ms]");
		Lexer lexer(iss);
		lexer.nextSymbol();
	}

	catch (const std::exception & e)
	{
		test = true;
	}

	EXPECT_TRUE(test);
}