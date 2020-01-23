#include "FunDefNode.h"

FunDefNode::FunDefNode(const std::string& id) : funId(id) {}

FunDefNode::~FunDefNode() {}

void FunDefNode::addParam(const std::string& param)
{
	paramList.push_back(param);
}

bool FunDefNode::execute(std::unique_ptr<Context>& context)
{
	for (auto it = context->functionList.begin(); it != context->functionList.end(); it++)
	{
		if (funId == (*it)->getFunId() && paramList.size() == (*it)->getParamListSize())
			throw std::runtime_error("ERROR: function already declared\n\t" + this->toString());
	}

	context->functionList.push_back(this);
	return false;
}

void FunDefNode::executeFunction(std::unique_ptr<Context>& context)
{
	auto argumentsIt = context->argList.begin();

	for (auto parametersIt = paramList.begin(); parametersIt != paramList.end(); parametersIt++)
	{
		context->localVariableList.push_back(
			std::make_shared<Variable>((*parametersIt), (*argumentsIt)));
		argumentsIt++;
	}

	context->argList.clear();

	for (auto childrenIt = children.begin(); childrenIt != children.end(); childrenIt++)
	{
		if ((*childrenIt)->execute(context)) break;
	}
}

std::string FunDefNode::getFunId()
{
	return funId;
}

unsigned int FunDefNode::getParamListSize()
{
	return paramList.size();
}

std::string FunDefNode::toString() const
{
	std::string text = "def " + funId + "(";
	for (auto it = paramList.begin(); it != paramList.end(); ++it) text = text + "var " + *it + ",";
	if (text.back() == ',') text.back() = ')';
	else text = text + ")";
	text = text + "{";
	for (auto it = children.begin(); it != children.end(); ++it) text = text + (*it)->toString();
	return text + "}";
}