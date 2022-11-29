//
// Created by Павло Коваль on 29.11.2022.
//

#ifndef DRUS_JA_TOKENTYPELIST_H
#define DRUS_JA_TOKENTYPELIST_H

#include <string>
#include <vector>

#include "TokenType.h"

namespace TokenTypes {
    const std::string PROGRAM = "PROGRAM";
    const std::string VAR = "VAR";
    const std::string START = "START";
    const std::string FINISH = "FINISH";
    const std::string INPUT = "INPUT";
    const std::string OUTPUT = "OUTPUT";
    const std::string ASSIGMENT = "ASSIGMENT";
    const std::string SEMICOLON = "SEMICOLON";
    const std::string STARTCYCLE = "STARTCYCLE";
    const std::string ENDCYCLE = "ENDCYCLE";
    const std::string PLUS = "PLUS";
    const std::string MINUS = "MINUS";
    const std::string MULTIPLY = "MULTIPLY";
    const std::string DIVIDE = "DIVIDE";
    const std::string MOD = "MOD";
    const std::string LPAREN = "LPAREN";
    const std::string RPAREN = "RPAREN";
    const std::string EQUAL = "EQUAL";
    const std::string NOTEQUAL = "NOTEQUAL";
    const std::string GREATER = "GREATER";
    const std::string LESS = "LESS";
    const std::string AND = "AND";
    const std::string OR = "OR";
    const std::string NOT = "NOT";
    const std::string DATATYPE = "DATATYPE";
    const std::string STARTCOMMENT = "StartComment";
    const std::string ENDCOMMENT = "EndComment";
    const std::string NEWLINE = "NEWLINE";
    const std::string SPACE = "SPACE";
}




typedef std::vector<TokenType> TokenList;


class TokenTypeList
{
private:
    static TokenList tokenTypeList;

public:
    TokenTypeList() = default;

    static TokenType &getTokenType();
    static TokenList &getTokenTypeList();
};


#endif //DRUS_JA_TOKENTYPELIST_H
