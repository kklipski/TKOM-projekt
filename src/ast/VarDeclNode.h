#pragma once

#include <stdexcept>
#include "AstNode.h"

class VarDeclNode : public AstNode
{
	friend class AstTest_VarDeclProperlyConvertedToAst_Test;
	friend class ParserTest_VarDeclParsedProperly_Test;

	std::string varId;

public:
	VarDeclNode(const std::string& id);
	~VarDeclNode();
	bool execute(std::unique_ptr<Context>& context);
	std::string toString() const override;
};