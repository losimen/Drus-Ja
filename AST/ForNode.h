// Drus_Ja by losimen 06.12.2022

#ifndef DRUS_JA_FORNODE_H
#define DRUS_JA_FORNODE_H

#include <utility>
#include <vector>

#include "INode.h"
#include "../Token.h"


struct ForNode: public INode
{
    std::vector<std::unique_ptr<INode>> nodes;
    std::unique_ptr<INode> stValue;
    std::unique_ptr<INode> ndValue;

    void add(std::unique_ptr<INode> &node)
    {
        nodes.push_back(std::move(node));
    }

    ForNode() = default;
};


#endif //DRUS_JA_FORNODE_H
