//
// Created by Павло Коваль on 29.11.2022.
//

#include "TokenTypeList.h"


TokenList TokenTypeList::tokenTypeList {
        TokenType("PROGRAM", "Program"),
        TokenType("VAR", "Var"),
        TokenType("START", "Start"),
        TokenType("FINISH", "Finish"),
        TokenType("INPUT", "Input"),
        TokenType("OUTPUT", "Output"),
        TokenType("ASSIGMENT", "->"),
        TokenType("SEMICOLON", ";"),
        TokenType("STARTCYCLE", "For"),
        TokenType("ENDCYCLE", "DownTo"),
        TokenType("PLUS", "+"),
        TokenType("MINUS", "-"),
        TokenType("MULTIPLY", "Mul"),
        TokenType("DIVIDE", "Div"),
        TokenType("MOD", "Mod"),
        TokenType("LPAREN", "("),
        TokenType("RPAREN", ")"),
        TokenType("EQUAL", "=="),
        TokenType("NOTEQUAL", "!="),
        TokenType("GREATER", "Ge"),
        TokenType("LESS", "Le"),
        TokenType("AND", "&&"),
        TokenType("OR", "||"),
        TokenType("NOT", "!!"),
        TokenType("DATATYPE", "Integer"),
        TokenType("StartComment", "/*"),
        TokenType("EndComment", "*/"),
};


TokenList &TokenTypeList::getTokenTypeList()
{
    return tokenTypeList;
}
