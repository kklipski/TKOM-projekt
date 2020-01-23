#pragma once

#include "AstNode.h"

class ElseBlockNode : public AstNode
{
	friend class ParserTest_ElseBlockParsedProperly_Test;
	friend class AstTest_ElseBlockProperlyConvertedToAst_Test;

public:
	~ElseBlockNode();
	bool execute(std::unique_ptr<Context>& context);
};