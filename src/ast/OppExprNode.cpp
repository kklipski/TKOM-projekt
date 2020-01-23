#include "OppExprNode.h"

OppExprNode::OppExprNode(bool flag) : isChildExpr(flag) {}

OppExprNode::~OppExprNode() {}

/* returned value is used here to get a result of function execution and does not result in ending 
program execution (execute() returns false) */
Constant OppExprNode::evaluate(std::unique_ptr<Context>& context)
{
	
	if (children.front()->execute(context))
	{
		auto toReturn = children.front()->evaluate(context);
		if (toReturn.nullObject) 
			throw std::runtime_error("ERROR: variable not defined (has no value assigned)\n\t" + 
				this->toString());
		else return toReturn;
	}

	else if (context->returnedValue.nullObject)	// called function returns no value
		throw std::runtime_error("ERROR: called function returns no value\n\t" + this->toString());

	else
	{
		auto toReturn = context->returnedValue;
		context->returnedValue = Constant(true);
		return toReturn;
	}
}

std::string OppExprNode::toString() const
{
	if (isChildExpr) return "(" + children.front()->toString() + ")";
	else return children.front()->toString();
}