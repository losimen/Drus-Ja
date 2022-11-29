//
// Created by Павло Коваль on 29.11.2022.
//

#ifndef DRUS_JA_TOKENTYPE_H
#define DRUS_JA_TOKENTYPE_H

#include <unordered_map>
#include <string>
#include <vector>


struct TokenType
{
    std::string name;
    std::string regex;

    TokenType() = delete;
    TokenType(const std::string &name, const std::string &regex);
};


#endif //DRUS_JA_TOKENTYPE_H
