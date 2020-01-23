#pragma once

#include <stdexcept>
#include "AstNode.h"

class OrExprNode : public AstNode
{
	friend class AstTest_OrExprProperlyConvertedToAst_Test;
	friend class ParserTest_OrExprParsedProperly_Test;

public:
	~OrExprNode();
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};