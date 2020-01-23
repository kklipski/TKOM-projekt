#include "AstNode.h"

Context::Context()
{
	result = std::string();
	returnedValue = Constant(true);	// null object
	looping = false;
	local = false;
}

AstNode::~AstNode() {}

void AstNode::addChild(std::unique_ptr<AstNode> child)
{
	children.push_back(std::move(child));
}

void AstNode::addParam(const std::string& param) {}

Constant AstNode::evaluate(std::unique_ptr<Context>& context)
{
	return Constant(0);
}

bool AstNode::execute(std::unique_ptr<Context>& context)
{
	return true;
}

void AstNode::executeFunction(std::unique_ptr<Context>& context) {}

std::string AstNode::getFunId()
{
	return std::string();
}

unsigned int AstNode::getParamListSize()
{
	return 0;
}

std::string AstNode::toString() const
{
	std::string text;
	for (auto it = children.begin(); it != children.end(); ++it) text = text + (*it)->toString();
	return text;
}