#include "pch.h"

struct AstTest : testing::Test {
	std::istringstream* iss;

	AstTest() {
		iss = new std::istringstream();
	}
	~AstTest() {
		delete iss;
	}
};

TEST_F(AstTest, AdditiveExprProperlyConvertedToAst) {
	iss->str("return 2*2;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <AdditiveExprNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front()->children.front().get());
	EXPECT_TRUE(node->children.size() == 2 && node->opList.front() == Operator::multiplicationOp);
}

TEST_F(AstTest, AndExprProperlyConvertedToAst) {
	iss->str("while(a>0){a=a-1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <AndExprNode*>(root->children.front()->children.front()->
		children.front()->children.front().get());
	EXPECT_TRUE(node->children.size() == 2 && node->opList.front() == Operator::greaterThanOp);
}

TEST_F(AstTest, ArgProperlyConvertedToAst) {
	iss->str("fun(arg);");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ArgNode*>(root->children.front()->children.front().get());
	EXPECT_EQ(node->children.size(), 1);
}

TEST_F(AstTest, AssignmentProperlyConvertedToAst) {
	iss->str("a=1;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <AssignmentNode*>(root->children.front().get());
	EXPECT_EQ(node->children.size(), 2);
}

TEST_F(AstTest, CharStringProperlyConvertedToAst) {
	iss->str("print(\"TKOM 2020\");");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <CharStringNode*>(root->children.front()->children.front().get());
	EXPECT_EQ(node->charString, "TKOM 2020");
}

TEST_F(AstTest, ConstantProperlyConvertedToAst) {
	iss->str("var a=1234[m];");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ConstantNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front()->children.front()->children.front()->
		children.front()->children.front().get());
	EXPECT_TRUE(node->constant.value == 1234 
		&& node->constant.unit == UnitDistribution(0, 1, 0));
}

TEST_F(AstTest, ElseBlockProperlyConvertedToAst) {
	iss->str("if(a==1){b=b+1;}else{c=c+1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ElseBlockNode*>((*(++(++(root->children.front()->
		children.begin())))).get());
	EXPECT_EQ(node->children.size(), 1);
}

TEST_F(AstTest, ExpressionProperlyConvertedToAst) {
	iss->str("if(a>0|b>0){print(\"At least one positive\");}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ExpressionNode*>(root->children.front()->children.front().get());
	EXPECT_EQ(node->children.size(), 2);
}

TEST_F(AstTest, FunCallProperlyConvertedToAst) {
	iss->str("fun(arg);");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <FunCallNode*>(root->children.front().get());
	EXPECT_TRUE(node->children.size() == 1 && node->funId == "fun");
}

TEST_F(AstTest, FunDefProperlyConvertedToAst) {
	iss->str("def fun(var a){a=a*a;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <FunDefNode*>(root->children.front().get());
	EXPECT_TRUE(node->children.size() == 1 && node->paramList.size() == 1 && node->funId == "fun");
}

TEST_F(AstTest, IdProperlyConvertedToAst) {
	iss->str("a=1;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <IdNode*>(root->children.front()->children.front().get());
	EXPECT_EQ(node->id, "a");
}

TEST_F(AstTest, IfBlockProperlyConvertedToAst) {
	iss->str("if(a==1){b=b+1;}else{c=c+1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <IfBlockNode*>((*(++(root->children.front()->
		children.begin()))).get());
	EXPECT_EQ(node->children.size(), 1);
}

TEST_F(AstTest, IfStatementProperlyConvertedToAst) {
	iss->str("if(a==1){b=b+1;}else{c=c+1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <IfStatementNode*>(root->children.front().get());
	EXPECT_EQ(node->children.size(), 3);
}

TEST_F(AstTest, MultiplicativeExprProperlyConvertedToAst) {
	iss->str("return -1;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <MultiplicativeExprNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front()->children.front()->
		children.front().get());
	EXPECT_TRUE(node->children.size() == 1 && node->op == Operator::subtractionOp);
}

TEST_F(AstTest, OppExprProperlyConvertedToAst) {
	iss->str("return -1;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <OppExprNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front()->children.front()->children.front()->
		children.front().get());
	EXPECT_EQ(node->children.size(), 1);
}

TEST_F(AstTest, OrExprProperlyConvertedToAst) {
	iss->str("if(a>0&b>0){print(\"Both positive\");}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <OrExprNode*>(root->children.front()->children.front()->
		children.front().get());
	EXPECT_EQ(node->children.size(), 2);
}

TEST_F(AstTest, PrintCallProperlyConvertedToAst) {
	iss->str("print(\"TKOM 2020\");");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <PrintCallNode*>(root->children.front().get());
	EXPECT_EQ(node->children.size(), 1);
}

TEST_F(AstTest, ProgramProperlyConvertedToAst) {
	iss->str("while(a>0){a=a-1;}print(\"a nulled\");");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	EXPECT_EQ(root->children.size(), 2);
}

TEST_F(AstTest, RelExprProperlyConvertedToAst) {
	iss->str("return 2+2;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <RelExprNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front().get());
	EXPECT_TRUE(node->children.size() == 2 && node->opList.front() == Operator::additionOp);
}

TEST_F(AstTest, ReturnStatementProperlyConvertedToAst) {
	iss->str("return 2*2;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ReturnStatementNode*>(root->children.front().get());
	EXPECT_EQ(node->children.size(), 1);
}

TEST_F(AstTest, VarDeclProperlyConvertedToAst) {
	iss->str("var a=1234;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <VarDeclNode*>(root->children.front().get());
	EXPECT_TRUE(node->children.size() == 1 && node->varId == "a");
}

TEST_F(AstTest, WhileStatementProperlyConvertedToAst) {
	iss->str("while(a>0){a=a-1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <WhileStatementNode*>(root->children.front().get());
	EXPECT_EQ(node->children.size(), 2);
}