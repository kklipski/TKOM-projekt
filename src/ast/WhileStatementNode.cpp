#include "WhileStatementNode.h"

WhileStatementNode::~WhileStatementNode() {}

bool WhileStatementNode::execute(std::unique_ptr<Context>& context)
{
	std::unique_ptr<Context> newContext = std::make_unique<Context>(std::list<Constant>(),
		context->functionList, context->globalVariableList, context->localVariableList,
		context->result, Constant(), false);

	while (children.front().get()->evaluate(context).value)
	{
		auto it = children.begin();
		it++;

		while (it != children.end())
		{
			if ((*it)->execute(newContext))
			{
				context->result = newContext->result;
				context->returnedValue = newContext->returnedValue;
				return true;
			}

			else it++;
		}

		newContext->looping = newContext->looping || 1;
	}

	context->result = newContext->result;
	context->returnedValue = newContext->returnedValue;
	return false;
}

std::string WhileStatementNode::toString() const
{
	auto it = children.begin();
	std::string text = "while(" + (*it)->toString() + "){";
	return text + (*++it)->toString() + "}";
}