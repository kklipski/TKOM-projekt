#pragma once

#include <stdexcept>
#include "AstNode.h"

class AndExprNode : public AstNode
{
	friend class AstTest_AndExprProperlyConvertedToAst_Test;
	friend class ParserTest_AndExprParsedProperly_Test;

	std::list<Operator> opList;

public:
	~AndExprNode();
	void addOperator(Operator op);
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};