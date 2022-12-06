// Drus_Ja by losimen 06.12.2022

#ifndef DRUS_JA_IFNODE_H
#define DRUS_JA_IFNODE_H

#include "IBlockNode.h"


struct IfNode: public IBlockNode
{
    std::unique_ptr<INode> condition;
};



#endif //DRUS_JA_IFNODE_H
