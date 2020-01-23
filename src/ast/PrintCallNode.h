#pragma once

#include <stdexcept>
#include "AstNode.h"

class PrintCallNode : public AstNode
{
	friend class AstTest_PrintCallProperlyConvertedToAst_Test;
	friend class ParserTest_PrintCallParsedProperly_Test;

public:
	~PrintCallNode();
	bool execute(std::unique_ptr<Context>& context);
	std::string toString() const;
};