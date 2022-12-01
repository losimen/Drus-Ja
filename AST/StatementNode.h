// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_STATEMENTNODE_H
#define DRUS_JA_STATEMENTNODE_H

#include <vector>

#include "INode.h"


struct StatementNode: public INode
{
    std::vector<std::unique_ptr<INode>> nodes;

    void add(std::unique_ptr<INode> &node)
    {
        nodes.push_back(std::move(node));
    }
};


#endif //DRUS_JA_STATEMENTNODE_H
