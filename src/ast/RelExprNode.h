#pragma once

#include <stdexcept>
#include "AstNode.h"

class RelExprNode : public AstNode
{
	friend class AstTest_RelExprProperlyConvertedToAst_Test;
	friend class ParserTest_RelExprParsedProperly_Test;

	std::list<Operator> opList;

public:
	~RelExprNode();
	void addOperator(Operator op);
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};