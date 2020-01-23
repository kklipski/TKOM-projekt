#pragma once

#include "AstNode.h"

class CharStringNode : public AstNode
{
	friend class AstTest_CharStringProperlyConvertedToAst_Test;
	friend class ParserTest_CharStringParsedProperly_Test;

	std::string charString;

public:
	CharStringNode(std::string text);
	~CharStringNode();
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};