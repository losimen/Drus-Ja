// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_UNAROPERATIONNODE_H
#define DRUS_JA_UNAROPERATIONNODE_H

#include "INode.h"
#include "../Token.h"


struct UnarOperationNode: public INode
{
    Token op;
    INode operand;

    UnarOperationNode(const Token &op, const INode &operand): op(op), operand(operand) {}
};


#endif //DRUS_JA_UNAROPERATIONNODE_H
