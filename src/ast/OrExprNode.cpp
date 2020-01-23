#include "OrExprNode.h"

OrExprNode::~OrExprNode() {}

Constant OrExprNode::evaluate(std::unique_ptr<Context>& context)
{
	auto childrenIter = children.begin();
	Constant toReturn = (*childrenIter)->evaluate(context);

	if ((++childrenIter) != children.end())
	{
		Constant currentConstant = toReturn, nextConstant;

		while (childrenIter != children.end())
		{
			nextConstant = (*childrenIter)->evaluate(context);
			toReturn = currentConstant && nextConstant;
			if (toReturn.nullObject)
				throw std::runtime_error("ERROR: inconsistent units\n\t" + this->toString());
			childrenIter++;
			currentConstant = nextConstant;
		}
	}

	return toReturn;
}

std::string OrExprNode::toString() const
{
	auto it = children.begin();
	std::string text = (*it)->toString();
	while (++it != children.end()) text = text + "&" + (*it)->toString();
	return text;
}