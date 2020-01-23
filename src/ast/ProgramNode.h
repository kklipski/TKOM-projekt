#pragma once

#include "AstNode.h"

class ProgramNode : public AstNode
{
	friend class AstTest_ProgramProperlyConvertedToAst_Test;
	friend class ParserTest_ProgramParsedProperly_Test;

public:
	~ProgramNode();
	std::string execute();
};