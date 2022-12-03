// Drus_Ja by losimen 29.11.2022


#ifndef DRUS_JA_TOKEN_H
#define DRUS_JA_TOKEN_H

#include <string>

#include "TokenType.h"


struct Token
{
    TokenType type;
    std::string value;

    unsigned line;
    unsigned row;
    unsigned pos;

    Token();
    Token(TokenType type, std::string value, unsigned line, unsigned row, unsigned pos);
};




#endif //DRUS_JA_TOKEN_H
