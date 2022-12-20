// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_UNAROPERATIONNODE_H
#define DRUS_JA_UNAROPERATIONNODE_H

#include <memory>

#include "INode.h"
#include "../Token.h"


struct UnarOperationNode: public INode
{
    Token op;
    std::unique_ptr<INode> operand;

    UnarOperationNode(const Token &op, std::unique_ptr<INode> &operand): op(op),
                                                                         operand(std::move(operand))
                                                                         {}
};


#endif //DRUS_JA_UNAROPERATIONNODE_H
