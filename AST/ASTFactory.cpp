// Drus_Ja by losimen 01.12.2022
#include "ASTFactory.h"


std::unique_ptr<INode> ASTFactory::createStatementNode()
{
    return std::unique_ptr<INode>();
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




