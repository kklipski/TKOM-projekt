#include "VarDeclNode.h"

VarDeclNode::VarDeclNode(const std::string& id) : varId(id) {}

VarDeclNode::~VarDeclNode() {}

bool VarDeclNode::execute(std::unique_ptr<Context>& context)
{
	if (context->local && !context->looping)
	{
		for (auto variablesIt = context->localVariableList.begin();
			variablesIt != context->localVariableList.end(); variablesIt++)
		{
			if (varId == (*variablesIt)->getId())
				throw std::runtime_error("ERROR: variable having such id already exists\n\t"
					+ this->toString());
		}

		if (!children.empty()) context->localVariableList.push_back(
			std::make_shared<Variable>(varId, children.front()->evaluate(context)));
		else context->localVariableList.push_back(std::make_shared<Variable>(varId));
	}

	else if (context->local && context->looping && !children.empty())
	{
		for (auto variablesIt = context->localVariableList.begin();
			variablesIt != context->localVariableList.end(); variablesIt++)
		{
			if (varId == (*variablesIt)->getId())
				(*variablesIt)->setAssignedConstant(children.front()->evaluate(context));
		}
	}
	
	else
	{
		for (auto variablesIt = context->globalVariableList.begin();
			variablesIt != context->globalVariableList.end(); variablesIt++)
		{
			if (varId == (*variablesIt)->getId())
				throw std::runtime_error("ERROR: variable having such id already exists\n\t"
					+ this->toString());
		}

		if (!children.empty()) context->globalVariableList.push_back(
			std::make_shared<Variable>(varId, children.front()->evaluate(context)));
		else context->globalVariableList.push_back(std::make_shared<Variable>(varId));
	}

	return false;
}

std::string VarDeclNode::toString() const
{
	std::string text = "var " + varId;
	if (!children.empty()) return text + "=" + children.front()->toString() + ";";
	else return text + ";";
}