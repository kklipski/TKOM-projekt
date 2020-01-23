#include "IfStatementNode.h"

IfStatementNode::~IfStatementNode() {}

bool IfStatementNode::execute(std::unique_ptr<Context>& context)
{
	auto expressionToEvaluate = children.front().get();
	auto it = children.begin();
	it++;

	if (expressionToEvaluate->evaluate(context).value)
	{
		if ((*it)->execute(context)) return true;
	}

	else
	{
		if ((++it) != children.end())
		{
			if ((*it)->execute(context)) return true;
		}
	}

	return false;
}

std::string IfStatementNode::toString() const
{
	auto it = children.begin();
	std::string text = "if(" + (*it)->toString() + "){";
	text = text + (*++it)->toString();
	if (++it != children.end()) return text + "}else{" + (*it)->toString() + "}";
	else return text + "}";
}