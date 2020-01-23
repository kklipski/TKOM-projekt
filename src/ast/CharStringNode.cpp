#include "CharStringNode.h"

CharStringNode::CharStringNode(std::string text) : charString(text) {}

CharStringNode::~CharStringNode() {}

Constant CharStringNode::evaluate(std::unique_ptr<Context>& context)
{
	context->result = context->result + charString + '\n';
	return Constant(true);
}

std::string CharStringNode::toString() const
{
	return charString;
}