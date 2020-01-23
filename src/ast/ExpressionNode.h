#pragma once

#include <stdexcept>
#include "AstNode.h"

class ExpressionNode : public AstNode
{
	friend class AstTest_ExpressionProperlyConvertedToAst_Test;
	friend class ParserTest_ExpressionParsedProperly_Test;

public:
	~ExpressionNode();
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};