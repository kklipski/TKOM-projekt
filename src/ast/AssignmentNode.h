#pragma once

#include <stdexcept>
#include "AstNode.h"

class AssignmentNode : public AstNode
{
	friend class ParserTest_AssignmentParsedProperly_Test;
	friend class AstTest_AssignmentProperlyConvertedToAst_Test;

public:
	~AssignmentNode();
	bool execute(std::unique_ptr<Context>& context);
	std::string toString() const;
};