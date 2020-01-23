#pragma once

#include <list>
#include <memory>
#include <string>
#include "Variable.h"

class AstNode;

struct Context
{
	std::list<Constant> argList;	// after assigning to parameters added to localVariableList
	std::list<AstNode*> functionList;
	std::list<std::shared_ptr<Variable>> globalVariableList;
	std::list<std::shared_ptr<Variable>> localVariableList;
	std::string result;
	Constant returnedValue;
	bool looping;	// we do not want to redeclare variables declared in while loop
	bool local;	// determine whether variable should be saved as global or local

	Context();
	Context(const std::list<Constant>& _argList, 
		const std::list<AstNode*>& _functionList,
		const std::list<std::shared_ptr<Variable>>& _globalVariableList,
		const std::list<std::shared_ptr<Variable>>& _localVariableList, const std::string& _result,
		const Constant& _returnedValue, const bool& _looping, const bool& _local = true) : 
		argList(_argList), functionList(_functionList), globalVariableList(_globalVariableList), 
		localVariableList(_localVariableList), result(_result), returnedValue(_returnedValue), 
		looping(_looping), local(_local) {}
};

class AstNode
{
	// test classes
	friend class AstTest_AdditiveExprProperlyConvertedToAst_Test;
	friend class AstTest_AndExprProperlyConvertedToAst_Test;
	friend class AstTest_ArgProperlyConvertedToAst_Test;
	friend class AstTest_AssignmentProperlyConvertedToAst_Test;
	friend class AstTest_CharStringProperlyConvertedToAst_Test;
	friend class AstTest_ConstantProperlyConvertedToAst_Test;
	friend class AstTest_ElseBlockProperlyConvertedToAst_Test;
	friend class AstTest_ExpressionProperlyConvertedToAst_Test;
	friend class AstTest_FunCallProperlyConvertedToAst_Test;
	friend class AstTest_FunDefProperlyConvertedToAst_Test;
	friend class AstTest_IdProperlyConvertedToAst_Test;
	friend class AstTest_IfBlockProperlyConvertedToAst_Test;
	friend class AstTest_IfStatementProperlyConvertedToAst_Test;
	friend class AstTest_MultiplicativeExprProperlyConvertedToAst_Test;
	friend class AstTest_OppExprProperlyConvertedToAst_Test;
	friend class AstTest_OrExprProperlyConvertedToAst_Test;
	friend class AstTest_PrintCallProperlyConvertedToAst_Test;
	friend class AstTest_ProgramProperlyConvertedToAst_Test;
	friend class AstTest_RelExprProperlyConvertedToAst_Test;
	friend class AstTest_ReturnStatementProperlyConvertedToAst_Test;
	friend class AstTest_VarDeclProperlyConvertedToAst_Test;
	friend class AstTest_WhileStatementProperlyConvertedToAst_Test;
	friend class ParserTest_AdditiveExprParsedProperly_Test;
	friend class ParserTest_AndExprParsedProperly_Test;
	friend class ParserTest_ArgParsedProperly_Test;
	friend class ParserTest_AssignmentParsedProperly_Test;
	friend class ParserTest_CharStringParsedProperly_Test;
	friend class ParserTest_ConstantParsedProperly_Test;
	friend class ParserTest_ElseBlockParsedProperly_Test;
	friend class ParserTest_ExpressionParsedProperly_Test;
	friend class ParserTest_FunCallParsedProperly_Test;
	friend class ParserTest_FunDefParsedProperly_Test;
	friend class ParserTest_IdParsedProperly_Test;
	friend class ParserTest_IfBlockParsedProperly_Test;
	friend class ParserTest_IfStatementParsedProperly_Test;
	friend class ParserTest_MultiplicativeExprParsedProperly_Test;
	friend class ParserTest_OppExprParsedProperly_Test;
	friend class ParserTest_OrExprParsedProperly_Test;
	friend class ParserTest_PrintCallParsedProperly_Test;
	friend class ParserTest_ProgramParsedProperly_Test;
	friend class ParserTest_RelExprParsedProperly_Test;
	friend class ParserTest_ReturnStatementParsedProperly_Test;
	friend class ParserTest_VarDeclParsedProperly_Test;
	friend class ParserTest_WhileStatementParsedProperly_Test;

protected:
	std::list<std::unique_ptr<AstNode>> children;

public:
	virtual ~AstNode();
	void addChild(std::unique_ptr<AstNode> child);
	virtual void addParam(const std::string& param);
	virtual Constant evaluate(std::unique_ptr<Context>& context);
	// true, if return statement
	virtual bool execute(std::unique_ptr<Context>& context);
	virtual void executeFunction(std::unique_ptr<Context>& context);
	virtual std::string getFunId();
	virtual unsigned int getParamListSize();
	virtual std::string toString() const;
};