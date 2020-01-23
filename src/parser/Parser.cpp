#include "Parser.h"

SymbolSet::SymbolSet(int element)
{
	for (int i = 0; i < wordsCount; i++) set[i] = 0;	// initialize empty set

	if (element >= 0 && element < size) set[element / unsignedBitsCount] =
		(1 << (element % unsignedBitsCount));
}

SymbolSet::SymbolSet(std::initializer_list<int> list)
{
	for (int i = 0; i < wordsCount; i++) set[i] = 0;	// initialize empty set

	for (auto element : list)
	{
		if (element < 0) break;	// argument list ending with EOS == -1

		if (element < size)	// ignore elements beyond the range
			set[element / unsignedBitsCount] |= (1 << (element % unsignedBitsCount));
	}
}

bool SymbolSet::has(int element) const
{
	if (element < 0 || element >= size) return 0;
	return ((set[element / unsignedBitsCount] & (1 << element % unsignedBitsCount)) != 0);
}

SymbolSet SymbolSet::operator+(const SymbolSet& secondSumComponent) const
{
	SymbolSet temp = *this;
	for (int i = 0; i < wordsCount; i++) temp.set[i] |= secondSumComponent.set[i];
	return temp;
}

const std::array<std::string, to_underlying(Token::MAX_SYMBOL)> Parser::atomTable =
{
	"def", "var", "while", "print", "if", "else", "return", "idAtom", "numberAtom",
	"charStringAtom", "unitAtom",

	";", "(", ")", "{", "}", "=", ",", "|", "&", "==", "!=", ">", ">=", "<", "<=", "+", "-", "*",
	"/", "!", "eof", "others"
};

const SymbolSet Parser::additiveOperators = 
	SymbolSet({ to_underlying(Token::plus), to_underlying(Token::minus), EOS });

const SymbolSet Parser::expressionSymbols =
	SymbolSet({ to_underlying(Token::notOperator), to_underlying(Token::minus), 
		to_underlying(Token::numberAtom), to_underlying(Token::leftRoundBracket), 
		to_underlying(Token::idAtom), EOS });

const SymbolSet Parser::multiplicativeOperators = 
	SymbolSet({ to_underlying(Token::times), to_underlying(Token::divisionOperator), EOS });

const SymbolSet Parser::relativeOperators = 
	SymbolSet({ to_underlying(Token::equalToOperator), to_underlying(Token::notEqualToOperator), 
		to_underlying(Token::greaterThanOperator), to_underlying(Token::greaterThanOrEqualToOperator), 
		to_underlying(Token::lessThanOperator), to_underlying(Token::lessThanOrEqualToOperator), EOS });

const SymbolSet Parser::startSymbols =
	SymbolSet({ to_underlying(Token::defSymbol), to_underlying(Token::ifSymbol), 
		to_underlying(Token::whileSymbol), to_underlying(Token::idAtom), 
		to_underlying(Token::printSymbol), to_underlying(Token::returnSymbol), 
		to_underlying(Token::varSymbol), EOS });

const SymbolSet Parser::statementSymbols =
	SymbolSet({ to_underlying(Token::ifSymbol), to_underlying(Token::whileSymbol), 
		to_underlying(Token::idAtom), to_underlying(Token::printSymbol), 
		to_underlying(Token::returnSymbol), to_underlying(Token::varSymbol), EOS });

void Parser::accept(Token atom)
{
	if (symbol == atom) nextSymbol();
	else expectedAtomSyntaxError(static_cast<int>(symbol));
}

void Parser::backToken(Token atom)
{
	if (backedSymbol != Token::MAX_SYMBOL)
	{
		std::runtime_error("Strange behaviour of parser...\n");
		return;
	}
	backedSymbol = symbol;
	symbol = atom;
}

void Parser::beginSync(const SymbolSet& symbolSet, const SymbolSet& followers)
{
	if (!symbolSet.has(static_cast<int>(symbol)))
	{
		unexpectedAtomSyntaxError(static_cast<int>(symbol));	// unexpected atom
		skipTo(symbolSet + followers);
	}
	canParse = symbolSet.has(static_cast<int>(symbol));
}

void Parser::endSync(const SymbolSet& followers)
{
	if (!followers.has(static_cast<int>(symbol)))
	{
		// unexpected atom
		unexpectedAtomSyntaxError(static_cast<int>(symbol));
		skipTo(followers);
	}
}

void Parser::expectedAtomSyntaxError(int atom)
{
	lexerModule.scanError(firstSyntaxError + atom, "Expected atom: ", atomTable[atom]);
}

void Parser::nextSymbol()
{
	if (backedSymbol == Token::MAX_SYMBOL) symbol = lexerModule.nextSymbol(); 
	else
	{
		symbol = backedSymbol;
		backedSymbol = Token::MAX_SYMBOL;
	}
}

void Parser::unexpectedAtomSyntaxError(int atom)
{
	lexerModule.scanError(firstSyntaxError + atom, "Unexpected atom: ", atomTable[atom]);
}

void Parser::skipTo(const SymbolSet& symbolSet)
{
	while (!symbolSet.has(static_cast<int>(symbol))) nextSymbol();
}

// PARSE PROCEDURES

void Parser::additiveExpr(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization delayed to mulitplicativeExpr() procedure
	if (!canParse) return;
	std::unique_ptr<AdditiveExprNode> newAdditiveExpr = std::make_unique<AdditiveExprNode>();
	multiplicativeExpr(followers + multiplicativeOperators, newAdditiveExpr.get());

	while (multiplicativeOperators.has(static_cast<int>(symbol)))
	{
		switch (symbol)
		{
		case Token::times:
			newAdditiveExpr.get()->addOperator(Operator::multiplicationOp);
			break;
		case Token::divisionOperator:
			newAdditiveExpr.get()->addOperator(Operator::divisionOp);
			break;
		default:
			break;
		}

		nextSymbol();
		multiplicativeExpr(followers + multiplicativeOperators, newAdditiveExpr.get());
	}

	currentNode->addChild(std::move(newAdditiveExpr));
}

void Parser::andExpr(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization delayed to mulitplicativeExpr() procedure
	if (!canParse) return;
	std::unique_ptr<AndExprNode> newAndExpr = std::make_unique<AndExprNode>();
	relExpr(followers + relativeOperators, newAndExpr.get());

	while (relativeOperators.has(static_cast<int>(symbol)))
	{
		switch (symbol)
		{
		case Token::equalToOperator:
			newAndExpr.get()->addOperator(Operator::equalToOp);
			break;
		case Token::notEqualToOperator:
			newAndExpr.get()->addOperator(Operator::notEqualToOp);
			break;
		case Token::greaterThanOperator:
			newAndExpr.get()->addOperator(Operator::greaterThanOp);
			break;
		case Token::greaterThanOrEqualToOperator:
			newAndExpr.get()->addOperator(Operator::greaterThanOrEqualToOp);
			break;
		case Token::lessThanOperator:
			newAndExpr.get()->addOperator(Operator::lessThanOp);
			break;
		case Token::lessThanOrEqualToOperator:
			newAndExpr.get()->addOperator(Operator::lessThanOrEqualToOp);
			break;
		default:
			break;
		}

		nextSymbol();
		relExpr(followers + relativeOperators, newAndExpr.get());
	}

	currentNode->addChild(std::move(newAndExpr));
}

void Parser::arg(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization delayed to mulitplicativeExpr() procedure
	if (!canParse) return;
	std::unique_ptr<ArgNode> newArg = std::make_unique<ArgNode>();
	expression(followers, newArg.get());
	currentNode->addChild(std::move(newArg));
}

void Parser::argList(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization delayed to mulitplicativeExpr() procedure
	if (!canParse) return;

	if (expressionSymbols.has(static_cast<int>(symbol)))
	{
		arg(followers + to_underlying(Token::comma), currentNode);

		while (symbol == Token::comma)
		{
			accept(Token::comma);
			arg(followers + to_underlying(Token::comma), currentNode);
		}
	}
}

void Parser::assignment(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization two levels up
	if (!canParse) return;
	std::unique_ptr<AssignmentNode> newAssignment = std::make_unique<AssignmentNode>();

	if (symbol == Token::idAtom)
	{
		std::unique_ptr<IdNode> newId = std::make_unique<IdNode>(lexerModule.getConstructedString());
		newAssignment->addChild(std::move(newId));
	}

	accept(Token::idAtom);
	accept(Token::assignmentOperator);
	expression(followers, newAssignment.get());
	currentNode->addChild(std::move(newAssignment));
}

void Parser::conditionalStatement(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization in statement() procedure
	if (!canParse) return;

	switch (symbol)
	{
	case Token::ifSymbol:
		ifStatement(followers, currentNode);
		break;
	case Token::whileSymbol:
		whileStatement(followers, currentNode);
		break;
	default:
		break;
	}
}

void Parser::constant(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization in multiplicativeExpr() procedure
	if (!canParse) return;
	accept(Token::numberAtom);
	std::unique_ptr<ConstantNode> newConstant;

	if (symbol == Token::unitAtom)
	{
		newConstant = std::make_unique<ConstantNode>(lexerModule.getConstructedNumber(), 
				lexerModule.getRecognizedUnit());
		accept(Token::unitAtom);
	}

	else newConstant = std::make_unique<ConstantNode>(lexerModule.getConstructedNumber(),
		Unit::NUMBER_OF_UNITS);	// no unit
	currentNode->addChild(std::move(newConstant));
}

void Parser::elseBlock(const SymbolSet& followers, AstNode* currentNode)
{
	beginSync(followers + to_underlying(Token::elseSymbol), followers);
	if (!canParse) return;
	std::unique_ptr<ElseBlockNode> newElseBlock = std::make_unique<ElseBlockNode>();

	if (symbol == Token::elseSymbol)
	{
		accept(Token::elseSymbol);
		accept(Token::leftCurlyBracket);

		do {
			statement(statementSymbols + to_underlying(Token::rightCurlyBracket), newElseBlock.get());
		} while (statementSymbols.has(static_cast<int>(symbol)));

		accept(Token::rightCurlyBracket);
	}

	currentNode->addChild(std::move(newElseBlock));
	endSync(followers);
}

void Parser::expression(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization delayed to mulitplicativeExpr() procedure
	if (!canParse) return;
	std::unique_ptr<ExpressionNode> newExpression = std::make_unique<ExpressionNode>();
	orExpr(followers + to_underlying(Token::orOperator), newExpression.get());

	while (symbol == Token::orOperator)
	{
		accept(Token::orOperator);
		orExpr(followers + to_underlying(Token::orOperator), newExpression.get());
	}

	currentNode->addChild(std::move(newExpression));
}

void Parser::funCall(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization two levels up
	if (!canParse) return;
	std::unique_ptr<FunCallNode> newFunCall;
	if (symbol == Token::idAtom) 
		newFunCall = std::make_unique<FunCallNode>(lexerModule.getConstructedString());
	accept(Token::idAtom);
	accept(Token::leftRoundBracket);
	argList(to_underlying(Token::rightRoundBracket), newFunCall.get());
	accept(Token::rightRoundBracket);
	currentNode->addChild(std::move(newFunCall));
}

void Parser::funDef(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization in progStatement() procedure
	if (!canParse) return;
	accept(Token::defSymbol);
	std::unique_ptr<FunDefNode> newFunDef;
	if (symbol == Token::idAtom) 
		newFunDef = std::make_unique<FunDefNode>(lexerModule.getConstructedString());
	accept(Token::idAtom);
	accept(Token::leftRoundBracket);
	paramList(to_underlying(Token::rightRoundBracket), newFunDef.get());
	accept(Token::rightRoundBracket);
	accept(Token::leftCurlyBracket);

	do {
		statement(statementSymbols + to_underlying(Token::rightCurlyBracket), newFunDef.get());
	} while (statementSymbols.has(static_cast<int>(symbol)));

	accept(Token::rightCurlyBracket);
	currentNode->addChild(std::move(newFunDef));
}

void Parser::ifBlock(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization in statement() procedure
	if (!canParse) return;
	std::unique_ptr<IfBlockNode> newIfBlock = std::make_unique<IfBlockNode>();
	accept(Token::ifSymbol);
	accept(Token::leftRoundBracket);
	expression(to_underlying(Token::rightRoundBracket), currentNode);
	accept(Token::rightRoundBracket);
	accept(Token::leftCurlyBracket);

	do {
		statement(statementSymbols + to_underlying(Token::rightCurlyBracket), newIfBlock.get());
	} while (statementSymbols.has(static_cast<int>(symbol)));

	accept(Token::rightCurlyBracket);
	currentNode->addChild(std::move(newIfBlock));
}

void Parser::ifStatement(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization two levels up
	if (!canParse) return;
	std::unique_ptr<IfStatementNode> newIfStatement = std::make_unique<IfStatementNode>();
	ifBlock(followers + to_underlying(Token::elseSymbol), newIfStatement.get());
	elseBlock(followers, newIfStatement.get());
	currentNode->addChild(std::move(newIfStatement));
}

void Parser::multiplicativeExpr(const SymbolSet& followers, AstNode* currentNode)
{
	beginSync(expressionSymbols, followers);
	if (!canParse) return;
	std::unique_ptr<MultiplicativeExprNode> newMultiplicativeExpr;
	
	if (symbol == Token::notOperator || symbol == Token::minus)
	{
		switch (symbol)
		{
		case Token::minus:
			newMultiplicativeExpr = std::make_unique<MultiplicativeExprNode>(Operator::subtractionOp);
			break;
		case Token::notOperator:
			newMultiplicativeExpr = std::make_unique<MultiplicativeExprNode>(Operator::notOp);
			break;
		default:
			break;
		}

		nextSymbol();
	}

	// no operator
	else newMultiplicativeExpr = std::make_unique<MultiplicativeExprNode>(Operator::MAX_OPERATOR);
	oppExpr(followers, newMultiplicativeExpr.get());
	currentNode->addChild(std::move(newMultiplicativeExpr));
	endSync(followers);
}

void Parser::oppExpr(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization in multiplicativeExpr() procedure
	if (!canParse) return;
	std::unique_ptr<OppExprNode> newOppExpr;

	switch (symbol)
	{
	case Token::numberAtom:
		newOppExpr = std::make_unique<OppExprNode>();
		constant(followers, newOppExpr.get());
		break;
	case Token::leftRoundBracket:
		newOppExpr = std::make_unique<OppExprNode>(true);
		accept(Token::leftRoundBracket);
		expression(to_underlying(Token::rightRoundBracket), newOppExpr.get());
		accept(Token::rightRoundBracket);
		break;
	case Token::idAtom:
		newOppExpr = std::make_unique<OppExprNode>();
		nextSymbol();

		if (symbol == Token::leftRoundBracket)
		{
			backToken(Token::idAtom);
			funCall(followers, newOppExpr.get());
		}

		else
		{
			backToken(Token::idAtom);
			std::unique_ptr<IdNode> newId = 
				std::make_unique<IdNode>(lexerModule.getConstructedString());
			newOppExpr->addChild(std::move(newId));
			accept(Token::idAtom);
		}

		break;
	default:
		break;
	}

	currentNode->addChild(std::move(newOppExpr));
}

void Parser::orExpr(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization delayed to mulitplicativeExpr() procedure
	if (!canParse) return;
	std::unique_ptr<OrExprNode> newOrExpr = std::make_unique<OrExprNode>();
	andExpr(followers + to_underlying(Token::andOperator), newOrExpr.get());

	while (symbol == Token::andOperator)
	{
		accept(Token::andOperator);
		andExpr(followers + to_underlying(Token::andOperator), newOrExpr.get());
	}

	currentNode->addChild(std::move(newOrExpr));
}

void Parser::param(const SymbolSet& followers, AstNode* currentNode)
{
	beginSync(to_underlying(Token::varSymbol), followers);
	if (!canParse) return;
	accept(Token::varSymbol);
	if (symbol == Token::idAtom) currentNode->addParam(lexerModule.getConstructedString());
	accept(Token::idAtom);
	endSync(followers);
}

void Parser::paramList(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization delayed to param() procedure
	if (!canParse) return;

	if (symbol == Token::varSymbol)
	{
		param(followers + to_underlying(Token::comma), currentNode);
		while (symbol == Token::comma)
		{
			accept(Token::comma);
			param(followers + to_underlying(Token::comma), currentNode);
		}
	}
}

void Parser::printCall(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization two levels up
	if (!canParse) return;
	std::unique_ptr<PrintCallNode> newPrintCall = std::make_unique<PrintCallNode>();
	accept(Token::printSymbol);
	accept(Token::leftRoundBracket);
	if (expressionSymbols.has(static_cast<int>(symbol))) 
		expression(to_underlying(Token::rightRoundBracket), newPrintCall.get());

	else
	{
		if (symbol == Token::charStringAtom)
		{
			std::unique_ptr<CharStringNode> newCharString = 
				std::make_unique<CharStringNode>(lexerModule.getConstructedString());
			newPrintCall->addChild(std::move(newCharString));
		}
		
		accept(Token::charStringAtom);
	}

	accept(Token::rightRoundBracket);
	currentNode->addChild(std::move(newPrintCall));
}

void Parser::progStatement(const SymbolSet& followers, AstNode* currentNode)
{
	beginSync(startSymbols, followers);
	if (!canParse) return;

	switch (symbol)
	{
	case Token::defSymbol:
		funDef(followers, currentNode);
		break;
	case Token::ifSymbol: case Token::whileSymbol: case Token::idAtom: case Token::printSymbol: 
	case Token::returnSymbol: case Token::varSymbol:
		statement(followers, currentNode);
		break;	
	default:
		break;
	}

	endSync(followers);
}

void Parser::relExpr(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization delayed to mulitplicativeExpr() procedure
	if (!canParse) return;
	std::unique_ptr<RelExprNode> newRelExpr = std::make_unique<RelExprNode>();
	additiveExpr(followers + additiveOperators, newRelExpr.get());

	while (additiveOperators.has(static_cast<int>(symbol)))
	{
		switch (symbol)
		{
		case Token::plus:
			newRelExpr.get()->addOperator(Operator::additionOp);
			break;
		case Token::minus:
			newRelExpr.get()->addOperator(Operator::subtractionOp);
			break;
		default:
			break;
		}

		nextSymbol();
		additiveExpr(followers + additiveOperators, newRelExpr.get());
	}

	currentNode->addChild(std::move(newRelExpr));
}

void Parser::returnStatement(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization in statement() procedure
	if (!canParse) return;
	std::unique_ptr<ReturnStatementNode> newReturnStatement = std::make_unique<ReturnStatementNode>();
	accept(Token::returnSymbol);
	expression(followers, newReturnStatement.get());
	currentNode->addChild(std::move(newReturnStatement));
}

void Parser::simpleStatement(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization in statement() procedure
	if (!canParse) return;

	switch (symbol)
	{
	case Token::idAtom:
		nextSymbol();

		switch (symbol)
		{
		case Token::assignmentOperator:
			backToken(Token::idAtom);
			assignment(to_underlying(Token::semicolon), currentNode);
			break;
		case Token::leftRoundBracket:
			backToken(Token::idAtom);
			funCall(to_underlying(Token::semicolon), currentNode);
			break;
		default:
			break;
		}

		break;
	case Token::printSymbol:
		printCall(to_underlying(Token::semicolon), currentNode);
		break;
	case Token::returnSymbol:
		returnStatement(to_underlying(Token::semicolon), currentNode);
		break;
	case Token::varSymbol:
		varDecl(to_underlying(Token::semicolon), currentNode);
		break;
	default:
		break;
	}

	accept(Token::semicolon);
}

void Parser::statement(const SymbolSet& followers, AstNode* currentNode)
{
	beginSync(statementSymbols, followers);
	if (!canParse) return;

	switch (symbol)
	{
	case Token::ifSymbol: case Token::whileSymbol:
		conditionalStatement(followers, currentNode);
		break;
	case Token::idAtom: case Token::printSymbol: case Token::returnSymbol: case Token::varSymbol:
		simpleStatement(followers, currentNode);
		break;
	default:
		break;
	}

	endSync(followers);
}

void Parser::varDecl(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization one level up
	if (!canParse) return;
	accept(Token::varSymbol);
	std::unique_ptr<VarDeclNode> newVarDecl;
	if (symbol == Token::idAtom) 
		newVarDecl = std::make_unique<VarDeclNode>(lexerModule.getConstructedString());
	accept(Token::idAtom);

	if (symbol == Token::assignmentOperator)
	{
		accept(Token::assignmentOperator);
		expression(followers, newVarDecl.get());
	}

	currentNode -> addChild(std::move(newVarDecl));
}

void Parser::whileStatement(const SymbolSet& followers, AstNode* currentNode)
{
	// synchronization in statement() procedure
	if (!canParse) return;
	std::unique_ptr<WhileStatementNode> newWhileStatement = std::make_unique<WhileStatementNode>();
	accept(Token::whileSymbol);
	accept(Token::leftRoundBracket);
	expression(to_underlying(Token::rightRoundBracket), newWhileStatement.get());
	accept(Token::rightRoundBracket);
	accept(Token::leftCurlyBracket);

	do
	{
		statement(statementSymbols + to_underlying(Token::rightCurlyBracket), 
			newWhileStatement.get());
	} while (statementSymbols.has(static_cast<int>(symbol)));

	accept(Token::rightCurlyBracket);
	currentNode->addChild(std::move(newWhileStatement));
}

// PARSE PROCEDURES END

Parser::Parser(Lexer& lexer):lexerModule(lexer)
{
	backedSymbol = Token::MAX_SYMBOL;	// 'no preceding atom' marker
	nextSymbol();	// get first atom
}

std::unique_ptr<ProgramNode> Parser::program()
{
	astRoot = std::make_unique<ProgramNode>();

	do {
		progStatement(startSymbols + to_underlying(Token::endOfFile), astRoot.get());
	} while (startSymbols.has(static_cast<int>(symbol)));

	return std::move(astRoot);
}