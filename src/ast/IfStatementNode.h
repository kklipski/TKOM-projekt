#pragma once

#include "AstNode.h"

class IfStatementNode : public AstNode
{
	friend class AstTest_IfStatementProperlyConvertedToAst_Test;
	friend class ParserTest_IfStatementParsedProperly_Test;

public:
	virtual ~IfStatementNode();
	bool execute(std::unique_ptr<Context>& context);
	std::string toString() const;
};