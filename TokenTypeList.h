//
// Created by Павло Коваль on 29.11.2022.
//

#ifndef DRUS_JA_TOKENTYPELIST_H
#define DRUS_JA_TOKENTYPELIST_H


#include <string>
#include <vector>

#include "TokenType.h"

typedef std::vector<TokenType> TokenList;


class TokenTypeList
{
private:
    static TokenList tokenTypeList;

public:
    TokenTypeList() = default;

    static TokenList &getTokenTypeList();
};


#endif //DRUS_JA_TOKENTYPELIST_H
