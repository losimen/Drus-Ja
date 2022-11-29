//
// Created by Павло Коваль on 29.11.2022.
//

#ifndef DRUS_JA_TOKEN_H
#define DRUS_JA_TOKEN_H


#include <string>

#include "TokenType.h"


struct Token
{
    TokenType type;
    std::string value;
    unsigned pos;

    Token() = default;
};




#endif //DRUS_JA_TOKEN_H
