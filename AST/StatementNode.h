// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_STATEMENTNODE_H
#define DRUS_JA_STATEMENTNODE_H

#include <vector>

#include "INode.h"


struct StatementNode: public INode
{
    std::vector<INode> nodes;

    void add(INode node)
    {
        nodes.push_back(node);
    }
};


#endif //DRUS_JA_STATEMENTNODE_H
