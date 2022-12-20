// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_BINOPERATIONNODE_H
#define DRUS_JA_BINOPERATIONNODE_H

#include <memory>

#include "INode.h"
#include "../Token.h"


struct BinOperationNode: public INode
{
    Token op;
    std::unique_ptr<INode> leftOperand;
    std::unique_ptr<INode> rightOperand;

    BinOperationNode() = delete;

    BinOperationNode(const Token &op, std::unique_ptr<INode> &leftOperand, std::unique_ptr<INode> &rightOperand) :
                               op(op),
                               leftOperand(std::move(leftOperand)),
                               rightOperand(std::move(rightOperand))
                               {}
};



#endif //DRUS_JA_BINOPERATIONNODE_H
