#pragma once

#include "AstNode.h"

class ArgNode : public AstNode
{
	friend class AstTest_ArgProperlyConvertedToAst_Test;
	friend class ParserTest_ArgParsedProperly_Test;

public:
	~ArgNode();
	Constant evaluate(std::unique_ptr<Context>& context);
};