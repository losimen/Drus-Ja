// Drus_Ja by losimen 06.12.2022

#ifndef DRUS_JA_IFNODE_H
#define DRUS_JA_IFNODE_H

#include "INode.h"


struct IfNode: public INode
{
    std::unique_ptr<INode> condition;
    std::unique_ptr<INode> ifBody;
    std::unique_ptr<INode> elseBody;
};



#endif //DRUS_JA_IFNODE_H
