#include "FunCallNode.h"

FunCallNode::FunCallNode(const std::string& id) : funId(id) {}

FunCallNode::~FunCallNode() {}

bool FunCallNode::execute(std::unique_ptr<Context>& context)
{
	unsigned int numberOfArguments = children.size();
	bool found = false;
	auto functionIt = context->functionList.begin();

	for (; functionIt != context->functionList.end(); functionIt++)
	{
		if (funId == (*functionIt)->getFunId()
			&& numberOfArguments == (*functionIt)->getParamListSize())
		{
			found = true;
			break;
		}
	}

	if (found)
	{
		std::unique_ptr<Context> newContext = std::make_unique<Context>(std::list<Constant>(),
			context->functionList, context->globalVariableList, std::list<std::shared_ptr<Variable>>(),
			context->result, Constant(), false);

		for (auto childrenIt = children.begin(); childrenIt != children.end(); childrenIt++)
		{
			newContext->argList.push_back((*childrenIt)->evaluate(context));
		}

		(*functionIt)->executeFunction(newContext);
		context->result = newContext->result;
		context->returnedValue = newContext->returnedValue;
	}

	else throw std::runtime_error("ERROR: function not recognized\n\t" + this->toString());
	return false;
}

std::string FunCallNode::toString() const
{
	std::string text = funId + "(";
	for (auto it = children.begin(); it != children.end(); ++it) 
		text = text + (*it)->toString() + ",";
	if (text.back() == ',') text.back() = ')';
	else text = text + ")";
	return text + ";";
}