#include "RelExprNode.h"

RelExprNode::~RelExprNode() {}

void RelExprNode::addOperator(Operator op)
{
	opList.push_back(op);
}

Constant RelExprNode::evaluate(std::unique_ptr<Context>& context)
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
			case Operator::additionOp:
				toReturn = toReturn + nextConstant;
				break;
			case Operator::subtractionOp:
				toReturn = toReturn - nextConstant;
				break;
			default:
				break;
			}

			if (toReturn.nullObject)
				throw std::runtime_error("ERROR: inconsistent units\n\t" + this->toString());
			childrenIter++;
			operatorIter++;
		}
	}

	return toReturn;
}

std::string RelExprNode::toString() const
{
	auto itChildren = children.begin();
	auto itOperators = opList.begin();
	std::string text = (*itChildren)->toString();

	while (itOperators != opList.end())
	{
		switch (*(itOperators++))
		{
		case Operator::additionOp:
			text = text + "+";
			break;
		case Operator::subtractionOp:
			text = text + "-";
			break;
		default:
			break;
		}

		text = text + (*++itChildren)->toString();
	}

	return text;
}