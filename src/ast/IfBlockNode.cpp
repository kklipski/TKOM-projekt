#include "IfBlockNode.h"

IfBlockNode::~IfBlockNode() {}

bool IfBlockNode::execute(std::unique_ptr<Context>& context)
{
	std::unique_ptr<Context> newContext = std::make_unique<Context>(std::list<Constant>(),
		context->functionList, context->globalVariableList, context->localVariableList,
		context->result, Constant(), false);

	for (auto it = children.begin(); it != children.end(); it++)
	{
		if ((*it)->execute(newContext))
		{
			context->result = newContext->result;
			context->returnedValue = newContext->returnedValue;
			return true;
		}
	}

	context->result = newContext->result;
	context->returnedValue = newContext->returnedValue;
	return false;
}