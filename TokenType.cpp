// Drus_Ja by losimen 29.11.2022


#include "TokenType.h"


TokenType::TokenType(const std::string &name, const std::string &regex)
{
    this->name = name;
    this->regex = regex;
}


TokenType::TokenType()
{
    this->name = TokenTypes::UNDEFINED;
}
