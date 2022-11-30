//
// Created by Павло Коваль on 29.11.2022.
//

#include "TokenTypeList.h"

using namespace TokenTypes;


TokenList TokenTypeList::tokenTypeList
{
        TokenType(PROGRAM, "Program"),
        TokenType(VAR, "Var"),
        TokenType(START, "Start"),
        TokenType(FINISH, "Finish"),
        TokenType(INPUT, "Input"),
        TokenType(OUTPUT, "Output"),
        TokenType(VARIABLE, "[a-z]*"),
        TokenType(NUMBER, "^-?[0-9]\\d*"),
        TokenType(ASSIGMENT, "->"),
        TokenType(SEMICOLON, ";"),
        TokenType(STARTCYCLE, "For"),
        TokenType(ENDCYCLE, "DownTo"),
        TokenType(PLUS, "\\+"),
        TokenType(MINUS, "-"),
        TokenType(MULTIPLY, "Mul"),
        TokenType(DIVIDE, "Div"),
        TokenType(MOD, "Mod"),
        TokenType(LPAREN, "\\("),
        TokenType(RPAREN, "\\)"),
        TokenType(EQUAL, "=="),
        TokenType(NOTEQUAL, "!="),
        TokenType(GREATER, "Ge"),
        TokenType(LESS, "Le"),
        TokenType(AND, "&&"),
        TokenType(OR, "\\|\\|"),
        TokenType(NOT, "!!"),
        TokenType(DATATYPE, "Integer"),
        TokenType(STARTCOMMENT, "/\\*"),
        TokenType(ENDCOMMENT, "\\*/"),
        TokenType(NEWLINE, "\\n"),
        TokenType(SPACE, " ")
};


TokenList &TokenTypeList::getTokenTypeList()
{
    return tokenTypeList;
}

TokenType TokenTypeList::getTokenType(const std::string &name)
{
    // TODO: use stl
    for (auto &tokenType: tokenTypeList)
        if (tokenType.name == name)
            return tokenType;

    return TokenType();
}
