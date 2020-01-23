#include "AssignmentNode.h"

AssignmentNode::~AssignmentNode() {}

bool AssignmentNode::execute(std::unique_ptr<Context>& context)
{
	auto childrenIt = children.begin();
	auto varId = (*childrenIt)->toString();
	auto valueToAssign = (*(++childrenIt))->evaluate(context);
	Constant valueAlreadyAssigned;
	bool found = false;
	auto localVariablesIt = context->localVariableList.begin();

	for (;localVariablesIt != context->localVariableList.end(); localVariablesIt++)
	{
		if (varId == (*localVariablesIt)->getId())
		{
			valueAlreadyAssigned = (*localVariablesIt)->getAssignedConstant();
			found = true;
			break;
		}
	}

	if (found)
	{
		if (valueAlreadyAssigned.nullObject)
			(*localVariablesIt)->setAssignedConstant(valueToAssign);
		else
			if (valueAlreadyAssigned.unit != valueToAssign.unit)
				throw std::runtime_error("ERROR: attempt to change unit of already initialized variable\n\t"
					+ this->toString());
			else (*localVariablesIt)->setAssignedConstant(valueToAssign);
		return false;
	}

	auto globalVariablesIt = context->globalVariableList.begin();

	for (;globalVariablesIt != context->globalVariableList.end(); globalVariablesIt++)
	{
		if (varId == (*globalVariablesIt)->getId())
		{
			valueAlreadyAssigned = (*globalVariablesIt)->getAssignedConstant();
			found = true;
			break;
		}
	}

	if (found)
	{
		if (valueAlreadyAssigned.nullObject)
			(*globalVariablesIt)->setAssignedConstant(valueToAssign);
		else
			if (valueAlreadyAssigned.unit != valueToAssign.unit)
				throw std::runtime_error("ERROR: attempt to change unit of initialized variable\n\t"
					+ this->toString());
			else (*globalVariablesIt)->setAssignedConstant(valueToAssign);
		return false;
	}

	throw std::runtime_error("ERROR: variable not declared\n\t" + this->toString());
}

std::string AssignmentNode::toString() const
{
	auto it = children.begin();
	std::string text = (*it)->toString() + "=";
	return text + (*++it)->toString() + ";";
}