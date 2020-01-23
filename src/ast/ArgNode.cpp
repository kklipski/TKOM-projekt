#include "ArgNode.h"

ArgNode::~ArgNode() {}

Constant ArgNode::evaluate(std::unique_ptr<Context>& context)
{
	return children.front()->evaluate(context);
}