// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_VARIABLENODE_H
#define DRUS_JA_VARIABLENODE_H

#include "INode.h"
#include "../Token.h"


struct VariableNode: public INode
{
    Token variable;

    VariableNode(Token variable)
    {
        this->variable = variable;
    }
};


#endif //DRUS_JA_VARIABLENODE_H
