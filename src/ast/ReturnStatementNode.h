#pragma once

#include <stdexcept>
#include "AstNode.h"

class ReturnStatementNode : public AstNode
{
	friend class AstTest_ReturnStatementProperlyConvertedToAst_Test;
	friend class ParserTest_ReturnStatementParsedProperly_Test;

public:
	~ReturnStatementNode();
	bool execute(std::unique_ptr<Context>& context);
	std::string toString() const;
};