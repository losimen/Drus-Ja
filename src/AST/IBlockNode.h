// Drus_Ja by losimen 06.12.2022

#ifndef DRUS_JA_IBLOCKNODE_H
#define DRUS_JA_IBLOCKNODE_H

#include <vector>

#include "INode.h"


struct IBlockNode: public INode
{
    std::vector<std::unique_ptr<INode>> nodes;

    void add(std::unique_ptr<INode> &node)
    {
        nodes.push_back(std::move(node));
    }
};



#endif //DRUS_JA_IBLOCKNODE_H
