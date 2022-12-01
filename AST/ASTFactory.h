// Drus_Ja by losimen 01.12.2022

#ifndef DRUS_JA_ASTFACTORY_H
#define DRUS_JA_ASTFACTORY_H

#include <memory>

#include "StatementNode.h"
#include "VariableNode.h"
#include "NumberNode.h"
#include "BinOperationNode.h"
#include "UnarOperationNode.h"
#include "ProgramNameNode.h"


class ASTFactory
{
public:
    ASTFactory() = delete;

    static std::unique_ptr<INode> createStatementNode();
    static std::unique_ptr<INode> createVariableNode(const Token &token);
    static std::unique_ptr<INode> createNumberNode(const Token &token);
    static std::unique_ptr<INode> createBinOperationNode(const Token &token,
                                                         std::unique_ptr<INode> &left,
                                                         std::unique_ptr<INode> &right);
    static std::unique_ptr<INode> createUnarOperationNode(const Token &token,
                                                          std::unique_ptr<INode> &operand);
    static std::unique_ptr<INode> createProgramNameNode(const Token &token);

};


#endif //DRUS_JA_ASTFACTORY_H
