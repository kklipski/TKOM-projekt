#pragma once

#include <stdexcept>
#include "AstNode.h"

class IdNode : public AstNode
{
	friend class AstTest_IdProperlyConvertedToAst_Test;
	friend class ParserTest_IdParsedProperly_Test;

	std::string id;

public:
	IdNode(const std::string& someId);
	~IdNode();
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};