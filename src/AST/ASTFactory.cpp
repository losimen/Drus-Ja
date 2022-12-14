// Drus_Ja by losimen 01.12.2022
#include "ASTFactory.h"


std::unique_ptr<INode> ASTFactory::createStatementNode()
{
    return std::make_unique<StatementNode>();
}


std::unique_ptr<INode> ASTFactory::createVariableNode(const Token &token)
{
    return std::make_unique<VariableNode>(token);
}


std::unique_ptr<INode> ASTFactory::createNumberNode(const Token &token)
{
    return std::make_unique<NumberNode>(token);
}


std::unique_ptr<INode> ASTFactory::createBinOperationNode(const Token &token,
                                                          std::unique_ptr<INode> &left,
                                                          std::unique_ptr<INode> &right)
{
    return std::make_unique<BinOperationNode>(token, left, right);
}


std::unique_ptr<INode> ASTFactory::createUnarOperationNode(const Token &token, std::unique_ptr<INode> &operand)
{
    return std::make_unique<UnarOperationNode>(token, operand);
}


std::unique_ptr<INode> ASTFactory::createProgramNameNode(const Token &token)
{
    return std::make_unique<ProgramNameNode>(token);
}


std::unique_ptr<INode> ASTFactory::createInitVariableNode(const Token &token, std::unique_ptr<INode> &value)
{
    return std::make_unique<InitVariableNode>(token, value);
}


std::unique_ptr<INode> ASTFactory::createForNode()
{
    return std::make_unique<ForNode>();
}


std::unique_ptr<INode> ASTFactory::createIfNode()
{
    return std::make_unique<IfNode>();
}


std::unique_ptr<INode> ASTFactory::createIfBodyNode()
{
    return std::make_unique<IfBodyNode>();
}


std::unique_ptr<INode> ASTFactory::createElseBodyNode()
{
    return std::make_unique<ElseBodyNode>();
}
