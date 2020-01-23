#include "ProgramNode.h"

ProgramNode::~ProgramNode() {}

std::string ProgramNode::execute()
{
	std::unique_ptr<Context> context = std::make_unique<Context>();
	std::string result;

	for (auto it = children.begin(); it != children.end(); it++)
	{
		if ((*it)->execute(context))
		{
			result = context->result + context->returnedValue.toString();
			result.pop_back();
			return result;
		}
	}

	result = context->result;
	if (result.back() == '\n') result.pop_back();
	return result;
}