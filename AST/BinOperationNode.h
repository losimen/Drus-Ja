// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_BINOPERATIONNODE_H
#define DRUS_JA_BINOPERATIONNODE_H

#include "INode.h"
#include "../Token.h"


struct BinOperationNode: public INode
{
    Token op;
    INode leftOperand;
    INode rightOperand;

    BinOperationNode(const Token &op,
                     const INode &leftOperand,
                     const INode &rightOperand): op(op), leftOperand(leftOperand), rightOperand(rightOperand)
                     {}
};



#endif //DRUS_JA_BINOPERATIONNODE_H
