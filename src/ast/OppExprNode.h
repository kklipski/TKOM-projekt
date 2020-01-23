#pragma once

#include <stdexcept>
#include "AstNode.h"

class OppExprNode : public AstNode
{
	friend class AstTest_OppExprProperlyConvertedToAst_Test;
	friend class ParserTest_OppExprParsedProperly_Test;

	bool isChildExpr;

public:
	OppExprNode(bool flag = 0);
	~OppExprNode();
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};