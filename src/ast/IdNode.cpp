#include "IdNode.h"

IdNode::IdNode(const std::string& someId) : id(someId) {}

IdNode::~IdNode() {}

Constant IdNode::evaluate(std::unique_ptr<Context>& context)
{
	for (auto localVariablesIt = context->localVariableList.begin();
		localVariablesIt != context->localVariableList.end(); localVariablesIt++)
	{
		if (id == (*localVariablesIt)->getId()) return (*localVariablesIt)->getAssignedConstant();
	}

	for (auto globalVariablesIt = context->globalVariableList.begin();
		globalVariablesIt != context->globalVariableList.end(); globalVariablesIt++)
	{
		if (id == (*globalVariablesIt)->getId()) return (*globalVariablesIt)->getAssignedConstant();
	}

	throw std::runtime_error("ERROR: variable does not exist\n\t" + this->toString());
}

std::string IdNode::toString() const
{
	return id;
}