#pragma once

#include <stdexcept>
#include "AstNode.h"

class FunCallNode : public AstNode
{
	friend class AstTest_FunCallProperlyConvertedToAst_Test;
	friend class ParserTest_FunCallParsedProperly_Test;

	std::string funId;

public:
	FunCallNode(const std::string& id);
	~FunCallNode();
	bool execute(std::unique_ptr<Context>& context);
	std::string toString() const;
};