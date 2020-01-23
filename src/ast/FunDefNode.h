#pragma once

#include <stdexcept>
#include "AstNode.h"

class FunDefNode : public AstNode
{
	friend class AstTest_FunDefProperlyConvertedToAst_Test;
	friend class ParserTest_FunDefParsedProperly_Test;
	friend class Function;

	std::string funId;
	std::list<std::string> paramList;

public:
	FunDefNode(const std::string& id);
	~FunDefNode();
	void addParam(const std::string& param);
	bool execute(std::unique_ptr<Context>& context);
	void executeFunction(std::unique_ptr<Context>& context);
	std::string getFunId();
	unsigned int getParamListSize();
	std::string toString() const override;
};