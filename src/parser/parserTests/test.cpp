#include "pch.h"

struct ParserTest : testing::Test {
	std::istringstream* iss;

	ParserTest() {
		iss = new std::istringstream();
	}
	~ParserTest() {
		delete iss;
	}
};

TEST_F(ParserTest, AdditiveExprParsedProperly) {
	iss->str("return 2*2;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <AdditiveExprNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front()->children.front().get());
	EXPECT_EQ(node->toString(), "2*2");
}

TEST_F(ParserTest, AndExprParsedProperly) {
	iss->str("while(a>0){a=a-1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <AndExprNode*>(root->children.front()->children.front()->
		children.front()->children.front().get());
	EXPECT_EQ(node->toString(), "a>0");
}

TEST_F(ParserTest, ArgParsedProperly) {
	iss->str("fun(arg);");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ArgNode*>(root->children.front()->children.front().get());
	EXPECT_EQ(node->toString(), "arg");
}

TEST_F(ParserTest, AssignmentParsedProperly) {
	iss->str("a=1;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <AssignmentNode*>(root->children.front().get());
	EXPECT_EQ(node->toString(), "a=1;");
}

TEST_F(ParserTest, CharStringParsedProperly) {
	iss->str("print(\"TKOM 2020\");");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <CharStringNode*>(root->children.front()->children.front().get());
	EXPECT_EQ(node->toString(), "TKOM 2020");
}

TEST_F(ParserTest, ConstantParsedProperly) {
	iss->str("var a=1234[m];");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ConstantNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front()->children.front()->children.front()->
		children.front()->children.front().get());
	EXPECT_EQ(node->toString(), "1234[m]");
}

TEST_F(ParserTest, ElseBlockParsedProperly) {
	iss->str("if(a==1){b=b+1;}else{c=c+1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ElseBlockNode*>((*(++(++(root->children.front()->
		children.begin())))).get());
	EXPECT_EQ(node->toString(), "c=c+1;");
}

TEST_F(ParserTest, ExpressionParsedProperly) {
	iss->str("if(a>0|b>0){print(\"At least one positive\");}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ExpressionNode*>(root->children.front()->
		children.front().get());
	EXPECT_EQ(node->toString(), "a>0|b>0");
}

TEST_F(ParserTest, FunCallParsedProperly) {
	iss->str("fun(arg);");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <FunCallNode*>(root->children.front().get());
	EXPECT_EQ(node->toString(), "fun(arg);");
}

TEST_F(ParserTest, FunDefParsedProperly) {
	iss->str("def fun(var a){a=a*a;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <FunDefNode*>(root->children.front().get());
	EXPECT_EQ(node->toString(), "def fun(var a){a=a*a;}");
}

TEST_F(ParserTest, IdParsedProperly) {
	iss->str("a=1;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <IdNode*>(root->children.front()->children.front().get());
	EXPECT_EQ(node->toString(), "a");
}

TEST_F(ParserTest, IfBlockParsedProperly) {
	iss->str("if(a==1){b=b+1;}else{c=c+1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <IfBlockNode*>((*(++(root->children.front()->
		children.begin()))).get());
	EXPECT_EQ(node->toString(), "b=b+1;");
}

TEST_F(ParserTest, IfStatementParsedProperly) {
	iss->str("if(a==1){b=b+1;}else{c=c+1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <IfStatementNode*>(root->children.front().get());
	EXPECT_EQ(node->toString(), "if(a==1){b=b+1;}else{c=c+1;}");
}

TEST_F(ParserTest, MultiplicativeExprParsedProperly) {
	iss->str("return -1;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <MultiplicativeExprNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front()->children.front()->
		children.front().get());
	EXPECT_EQ(node->toString(), "-1");
}

TEST_F(ParserTest, OppExprParsedProperly) {
	iss->str("return -1;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <OppExprNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front()->children.front()->children.front()->
		children.front().get());
	EXPECT_EQ(node->toString(), "1");
}

TEST_F(ParserTest, OrExprParsedProperly) {
	iss->str("if(a>0&b>0){print(\"Both positive\");}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <OrExprNode*>(root->children.front()->children.front()->
		children.front().get());
	EXPECT_EQ(node->toString(), "a>0&b>0");
}

TEST_F(ParserTest, PrintCallParsedProperly) {
	iss->str("print(\"TKOM 2020\");");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <PrintCallNode*>(root->children.front().get());
	EXPECT_EQ(node->toString(), "print(\"TKOM 2020\");");
}

TEST_F(ParserTest, ProgramParsedProperly) {
	iss->str("while(a>0){a=a-1;}print(\"a nulled\");");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	EXPECT_EQ(root->toString(), "while(a>0){a=a-1;}print(\"a nulled\");");
}

TEST_F(ParserTest, RelExprParsedProperly) {
	iss->str("return 2+2;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <RelExprNode*>(root->children.front()->children.front()->
		children.front()->children.front()->children.front().get());
	EXPECT_EQ(node->toString(), "2+2");
}

TEST_F(ParserTest, ReturnStatementParsedProperly) {
	iss->str("return 2*2;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <ReturnStatementNode*>(root->children.front().get());
	EXPECT_EQ(node->toString(), "return 2*2;");
}

TEST_F(ParserTest, VarDeclParsedProperly) {
	iss->str("var a=1234;");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <VarDeclNode*>(root->children.front().get());
	EXPECT_EQ(node->toString(), "var a=1234;");
}

TEST_F(ParserTest, WhileStatementParsedProperly) {
	iss->str("while(a>0){a=a-1;}");
	Lexer lexer(iss);
	Parser parser(lexer);
	auto root = std::move(parser.program());
	auto node = dynamic_cast <WhileStatementNode*>(root->children.front().get());
	EXPECT_EQ(node->toString(), "while(a>0){a=a-1;}");
}