#include "AndExprNode.h"

AndExprNode::~AndExprNode() {}

void AndExprNode::addOperator(Operator op)
{
	opList.push_back(op);
}

Constant AndExprNode::evaluate(std::unique_ptr<Context>& context)
{
	auto childrenIter = children.begin();
	Constant toReturn = (*childrenIter)->evaluate(context);

	if (!opList.empty())
	{
		childrenIter++;
		auto operatorIter = opList.begin();
		Constant currentConstant = toReturn, nextConstant;

		while (operatorIter != opList.end())
		{
			nextConstant = (*childrenIter)->evaluate(context);

			switch (*operatorIter)
			{
			case Operator::equalToOp:
				toReturn = currentConstant == nextConstant;
				break;
			case Operator::notEqualToOp:
				toReturn = currentConstant != nextConstant;
				break;
			case Operator::greaterThanOp:
				toReturn = currentConstant > nextConstant;
				break;
			case Operator::greaterThanOrEqualToOp:
				toReturn = currentConstant >= nextConstant;
				break;
			case Operator::lessThanOp:
				toReturn = currentConstant < nextConstant;
				break;
			case Operator::lessThanOrEqualToOp:
				toReturn = currentConstant <= nextConstant;
				break;
			default:
				break;
			}

			if (toReturn.nullObject)
				throw std::runtime_error("ERROR: inconsistent units\n\t" + this->toString());

			childrenIter++;
			operatorIter++;
			currentConstant = nextConstant;
		}
	}

	return toReturn;
}

std::string AndExprNode::toString() const
{
	auto itChildren = children.begin();
	auto itOperators = opList.begin();
	std::string text = (*itChildren)->toString();

	while (itOperators != opList.end())
	{
		switch (*(itOperators++))
		{
		case Operator::equalToOp:
			text = text + "==";
			break;
		case Operator::notEqualToOp:
			text = text + "!=";
			break;
		case Operator::greaterThanOp:
			text = text + ">";
			break;
		case Operator::greaterThanOrEqualToOp:
			text = text + ">=";
			break;
		case Operator::lessThanOp:
			text = text + "<";
			break;
		case Operator::lessThanOrEqualToOp:
			text = text + "<=";
			break;
		default:
			break;
		}

		text = text + (*++itChildren)->toString();
	}

	return text;
}