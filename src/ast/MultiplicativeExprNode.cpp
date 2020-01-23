#include "MultiplicativeExprNode.h"

MultiplicativeExprNode::MultiplicativeExprNode(Operator oper) : op(oper) {}

MultiplicativeExprNode::~MultiplicativeExprNode() {}

Constant MultiplicativeExprNode::evaluate(std::unique_ptr<Context>& context)
{
	switch (op)
	{
	case Operator::notOp:
		return !children.front()->evaluate(context);
	case Operator::subtractionOp:	// unary minus
		return -children.front()->evaluate(context);
	default:
		break;
	}

	return children.front()->evaluate(context);
}

std::string MultiplicativeExprNode::toString() const
{
	std::string text;

	switch (op)
	{
	case Operator::subtractionOp:
		text = text + "-";
		break;
	case Operator::notOp:
		text = text + "!";
		break;
	case Operator::MAX_OPERATOR:
		break;
	default:
		break;
	}

	text = text + children.front()->toString();
	return text;
}