#include "ReturnStatementNode.h"

ReturnStatementNode::~ReturnStatementNode() {}

bool ReturnStatementNode::execute(std::unique_ptr<Context>& context)
{
	context->returnedValue = children.front()->evaluate(context);
	if (context->returnedValue.unitNotDefined)	// unrecognized unit to be returned
		throw std::runtime_error("ERROR: returned unit not defined\n\t" + this->toString());
	else return true;
}

std::string ReturnStatementNode::toString() const
{
	std::string text = "return ";
	return text + (children.front())->toString() + ";";
}