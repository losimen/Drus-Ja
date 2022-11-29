//
// Created by Павло Коваль on 29.11.2022.
//

#include "TokenType.h"


TokenType::TokenType(const std::string &name, const std::string &regex)
{
    this->name = name;
    this->regex = regex;
}
