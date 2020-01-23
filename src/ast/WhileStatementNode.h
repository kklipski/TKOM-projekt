#pragma once

#include "AstNode.h"

class WhileStatementNode : public AstNode
{
	friend class AstTest_WhileStatementProperlyConvertedToAst_Test;
	friend class ParserTest_WhileStatementParsedProperly_Test;

public:
	~WhileStatementNode();
	bool execute(std::unique_ptr<Context>& context);
	std::string toString() const;
};