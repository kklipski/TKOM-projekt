#pragma once

#include "AstNode.h"

class AdditiveExprNode : public AstNode
{
	friend class AstTest_AdditiveExprProperlyConvertedToAst_Test;
	friend class ParserTest_AdditiveExprParsedProperly_Test;

	std::list<Operator> opList;

public:
	~AdditiveExprNode();
	void addOperator(Operator op);
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};