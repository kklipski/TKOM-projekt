#pragma once

#include "AstNode.h"

class IfBlockNode : public AstNode
{
	friend class AstTest_IfBlockProperlyConvertedToAst_Test;
	friend class ParserTest_IfBlockParsedProperly_Test;

public:
	~IfBlockNode();
	bool execute(std::unique_ptr<Context>& context);
};