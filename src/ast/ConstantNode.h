#pragma once

#include "AstNode.h"

class ConstantNode : public AstNode
{
	friend class AstTest_ConstantProperlyConvertedToAst_Test;
	friend class ParserTest_ConstantParsedProperly_Test;

	Constant constant;

	UnitDistribution findUnitDist(Unit unit);

public:
	ConstantNode(int number, Unit assignedUnit);
	~ConstantNode();
	Constant evaluate(std::unique_ptr<Context>& context);
	std::string toString() const;
};