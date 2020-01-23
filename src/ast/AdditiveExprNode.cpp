#include "AdditiveExprNode.h"

AdditiveExprNode::~AdditiveExprNode() {}

void AdditiveExprNode::addOperator(Operator op)
{
	opList.push_back(op);
}

Constant AdditiveExprNode::evaluate(std::unique_ptr<Context>& context)
{
	auto childrenIter = children.begin();
	Constant toReturn = (*childrenIter)->evaluate(context);

	if (!opList.empty())
	{
		childrenIter++;
		auto operatorIter = opList.begin();
		Constant nextConstant;

		while (operatorIter != opList.end())
		{
			nextConstant = (*childrenIter)->evaluate(context);

			switch (*operatorIter)
			{
			case Operator::multiplicationOp:
				toReturn = toReturn * nextConstant;
				break;
			case Operator::divisionOp:
				toReturn = toReturn / nextConstant;
				break;
			default:
				break;
			}

			childrenIter++;
			operatorIter++;
		}
	}

	return toReturn;
}

std::string AdditiveExprNode::toString() const
{
	auto itChildren = children.begin();
	auto itOperators = opList.begin();
	std::string text = (*itChildren)->toString();

	while (itOperators != opList.end())
	{
		switch (*(itOperators++))
		{
		case Operator::multiplicationOp:
			text = text + "*";
			break;
		case Operator::divisionOp:
			text = text + "/";
			break;
		default:
			break;
		}

		text = text + (*++itChildren)->toString();
	}

	return text;
}