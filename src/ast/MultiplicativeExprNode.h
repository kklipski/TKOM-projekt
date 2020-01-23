#pragma once

#include "AstNode.h"

class MultiplicativeExprNode : public AstNode
{
	friend class AstTest_MultiplicativeExprProperlyConvertedToAst_Test;
	friend class ParserTest_MultiplicativeExprParsedProperly_Test;

	Operator op;

public:
	MultiplicativeExprNode(Operator oper);
	~MultiplicativeExprNode();
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};