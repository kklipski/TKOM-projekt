#include "ConstantNode.h"

UnitDistribution ConstantNode::findUnitDist(Unit unit)
{
	for (int i = 0; i < to_underlying(Unit::NUMBER_OF_UNITS); i++)
	{
		if (unit == unitTable[i].unit) return unitTable[i].distribution;
	}

	return UnitDistribution();
}

ConstantNode::ConstantNode(int number, Unit assignedUnit) : 
	constant(Constant(number, findUnitDist(assignedUnit))) {}

ConstantNode::~ConstantNode() {}

Constant ConstantNode::evaluate(std::unique_ptr<Context>& context)
{
	return constant;
}

std::string ConstantNode::toString() const
{
	for (int i = 0; i < to_underlying(Unit::NUMBER_OF_UNITS); i++)
	{
		if (constant.unit == unitTable[i].distribution)
		{
			return std::to_string(constant.value) + "[" + unitTable[i].representation + "]";
		}
	}

	return std::to_string(constant.value);
}