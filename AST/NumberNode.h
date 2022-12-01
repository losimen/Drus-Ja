// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_NUMBERNODE_H
#define DRUS_JA_NUMBERNODE_H

#include "INode.h"
#include "../Token.h"


struct NumberNode: public INode
{
    Token number;

    NumberNode() = delete;
    NumberNode(Token number)
    {
        this->number = number;
    }
};


#endif //DRUS_JA_NUMBERNODE_H
