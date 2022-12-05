// Drus_Ja by losimen 29.11.2022

#include <algorithm>
#include "TokenTypeList.h"

using namespace TokenTypes;


TokenList TokenTypeList::tokenTypeList
{
        TokenType(PROGRAM, "Program"),
        TokenType(VARBLOCK, "Var"),
        TokenType(START, "Start"),
        TokenType(FINISH, "Finish"),
        TokenType(INPUT, "Input"),
        TokenType(OUTPUT, "Output"),
        TokenType(DATATYPE, "Integer"),
        TokenType(GREATER, "Ge"),
        TokenType(LESS, "Le"),
        TokenType(MULTIPLY, "Mul"),
        TokenType(DIVIDE, "Div"),
        TokenType(MOD, "Mod"),
        TokenType(VARIABLE, "(?=^[A-Z])([a-z]|[A-Z]){6}"),
        TokenType(NUMBER, "^-?[0-9]\\d*"),
        TokenType(ASSIGNMENT, "->"),
        TokenType(SEMICOLON, ";"),
        TokenType(STARTCYCLE, "For"),
        TokenType(ENDCYCLE, "DownTo"),
        TokenType(PLUS, "\\+"),
        TokenType(MINUS, "-"),
        TokenType(LPAREN, "\\("),
        TokenType(RPAREN, "\\)"),
        TokenType(EQUAL, "=="),
        TokenType(NOTEQUAL, "!="),
        TokenType(AND, "&&"),
        TokenType(OR, "\\|\\|"),
        TokenType(NOT, "!!"),
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
    auto isInList = std::find_if(tokenTypeList.begin(), tokenTypeList.end(),
                                 [&name](TokenType &str)
                                 {
                                     return name == str.name;
                                 });

    if (isInList != tokenTypeList.end())
    {
        return *isInList;
    }
    else
    {
        return {UNDEFINED, "Undefined"};
    }
}
