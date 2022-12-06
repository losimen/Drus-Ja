// Drus_Ja by losimen 06.12.2022

#ifndef DRUS_JA_FORNODE_H
#define DRUS_JA_FORNODE_H

#include <utility>
#include <vector>

#include "IBlockNode.h"
#include "../Token.h"


struct ForNode: public IBlockNode
{
    std::unique_ptr<INode> stValue;
    std::unique_ptr<INode> ndValue;
};


#endif //DRUS_JA_FORNODE_H
