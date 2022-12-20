// Drus_Ja by losimen 01.12.2022

#ifndef DRUS_JA_INITVARIABLENODE_H
#define DRUS_JA_INITVARIABLENODE_H

#include "INode.h"
#include "../Token.h"


struct InitVariableNode: public INode
{
    Token token;
    std::unique_ptr<INode> value;

    explicit InitVariableNode(const Token &token, std::unique_ptr<INode> &value): token(token), value(std::move(value)) {}
};


#endif //DRUS_JA_INITVARIABLENODE_H
