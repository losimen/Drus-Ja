// Drus_Ja by losimen 29.11.2022

#include "Token.h"

Token::Token()
{
    line = 0;
    row = 0;
    pos = 0;
}

Token::Token(TokenType type, const std::string &value, unsigned int line, unsigned int row, unsigned int pos)
{
    this->type = type;
    this->value = value;
    this->line = line;
    this->row = row;
    this->pos = pos;
}
