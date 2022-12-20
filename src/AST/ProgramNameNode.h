// Drus_Ja by losimen 01.12.2022

#ifndef DRUS_JA_PROGRAMNAMENODE_H
#define DRUS_JA_PROGRAMNAMENODE_H

#include "INode.h"
#include "../Token.h"


struct ProgramNameNode : public INode
{
    Token programName;

    ProgramNameNode() = delete;
    ProgramNameNode(Token programName)
    {
        this->programName = programName;
    }
};

#endif //DRUS_JA_PROGRAMNAMENODE_H
