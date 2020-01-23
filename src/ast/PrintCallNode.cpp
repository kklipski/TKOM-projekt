#include "PrintCallNode.h"

PrintCallNode::~PrintCallNode() {}

bool PrintCallNode::execute(std::unique_ptr<Context>& context)
{
	auto toPrint = children.front()->evaluate(context);
	if (toPrint.unitNotDefined) throw std::runtime_error("ERROR: printed unit not defined\n\t"
		+ this->toString());	// unrecognized unit to be printed
	else if (toPrint.nullObject) return false;	// printing charString
	else context->result = context->result + toPrint.toString();	// printing expression result
	return false;
}

std::string PrintCallNode::toString() const
{
	std::string text = "print(\"";
	return text + (children.front())->toString() + "\");";
}