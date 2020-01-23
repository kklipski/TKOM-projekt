#pragma once

#include "../ast/AdditiveExprNode.h"
#include "../ast/AndExprNode.h"
#include "../ast/ArgNode.h"
#include "../ast/AssignmentNode.h"
#include "../ast/CharStringNode.h"
#include "../ast/ConstantNode.h"
#include "../ast/ElseBlockNode.h"
#include "../ast/ExpressionNode.h"
#include "../ast/FunCallNode.h"
#include "../ast/FunDefNode.h"
#include "../ast/IdNode.h"
#include "../ast/IfBlockNode.h"
#include "../ast/IfStatementNode.h"
#include "../lexer/Lexer.h"
#include "../ast/MultiplicativeExprNode.h"
#include "../ast/OppExprNode.h"
#include "../ast/OrExprNode.h"
#include "../ast/PrintCallNode.h"
#include "../ast/ProgramNode.h"
#include "../ast/RelExprNode.h"
#include "../ast/ReturnStatementNode.h"
#include "../ast/VarDeclNode.h"
#include "../ast/WhileStatementNode.h"

class SymbolSet
{
	enum
	{
		CHAR_BIT = 8,
		size = to_underlying(Token::MAX_SYMBOL),	// set elements: 0, ..., (size - 1)
		unsignedBitsCount = (sizeof(unsigned) * CHAR_BIT),
		wordsCount = ((size - 1) / unsignedBitsCount + 1)
	};
	unsigned set[wordsCount];	// bit set representation

public:
	SymbolSet(int element);	// one-element set
	SymbolSet(std::initializer_list<int> list);	// any-number-of-elements set
	bool has(int element) const;	// check if 'element' is *this element
	SymbolSet operator+(const SymbolSet& secondSumComponent) const;	// *this + secondSumComponent
};

class Parser
{
	enum { EOS = -1 };	// 'end of element list' marker
	enum { firstSyntaxError = 10 };	// syntax errors' numbers are two-digit
	std::unique_ptr<ProgramNode> astRoot;
	static const std::array<std::string, to_underlying(Token::MAX_SYMBOL)> atomTable;
	Token backedSymbol;
	bool canParse;	// true if parser synchronized with input
	Lexer& lexerModule;
	Token symbol;

	static const SymbolSet additiveOperators;
	static const SymbolSet expressionSymbols;
	static const SymbolSet multiplicativeOperators;
	static const SymbolSet relativeOperators;
	static const SymbolSet startSymbols;
	static const SymbolSet statementSymbols;

	void accept(Token atom);
	void backToken(Token atom);
	void beginSync(const SymbolSet& symbolSet, const SymbolSet& followers);
	void endSync(const SymbolSet& followers);
	void expectedAtomSyntaxError(int atom);
	void nextSymbol();
	void skipTo(const SymbolSet& symbolSet);
	void unexpectedAtomSyntaxError(int atom);

	// parse procedures

	void additiveExpr(const SymbolSet& followers, AstNode* currentNode);
	void andExpr(const SymbolSet& followers, AstNode* currentNode);
	void arg(const SymbolSet& followers, AstNode* currentNode);
	void argList(const SymbolSet& followers, AstNode* currentNode);
	void assignment(const SymbolSet& followers, AstNode* currentNode);
	void conditionalStatement(const SymbolSet& followers, AstNode* currentNode);
	void constant(const SymbolSet& followers, AstNode* currentNode);
	void elseBlock(const SymbolSet& followers, AstNode* currentNode);
	void expression(const SymbolSet& followers, AstNode* currentNode);
	void funCall(const SymbolSet& followers, AstNode* currentNode);
	void funDef(const SymbolSet& followers, AstNode* currentNode);
	void ifBlock(const SymbolSet& followers, AstNode* currentNode);
	void ifStatement(const SymbolSet& followers, AstNode* currentNode);
	void multiplicativeExpr(const SymbolSet& followers, AstNode* currentNode);
	void oppExpr(const SymbolSet& followers, AstNode* currentNode);
	void orExpr(const SymbolSet& followers, AstNode* currentNode);
	void param(const SymbolSet& followers, AstNode* currentNode);
	void paramList(const SymbolSet& followers, AstNode* currentNode);
	void printCall(const SymbolSet& followers, AstNode* currentNode);
	void progStatement(const SymbolSet& followers, AstNode* currentNode);
	void relExpr(const SymbolSet& followers, AstNode* currentNode);
	void returnStatement(const SymbolSet& followers, AstNode* currentNode);
	void simpleStatement(const SymbolSet& followers, AstNode* currentNode);
	void statement(const SymbolSet& followers, AstNode* currentNode);
	void varDecl(const SymbolSet& followers, AstNode* currentNode);
	void whileStatement(const SymbolSet& followers, AstNode* currentNode);

public:
	Parser(Lexer& lexer);
	// main parse procedure, returns a smart pointer to the tree root
	std::unique_ptr<ProgramNode> program();
};