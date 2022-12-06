// Drus_Ja by losimen 29.11.2022


#ifndef DRUS_JA_TOKENTYPE_H
#define DRUS_JA_TOKENTYPE_H

#include <unordered_map>
#include <string>
#include <vector>


namespace TokenTypes
{
    const std::string UNDEFINED = "UNDEFINED";
    const std::string PROGRAM = "PROGRAM";
    const std::string VARBLOCK = "VARBLOCK";
    const std::string START = "START";
    const std::string FINISH = "FINISH";
    const std::string INPUT = "INPUT";
    const std::string OUTPUT = "OUTPUT";
    const std::string ASSIGNMENT = "ASSIGMENT";
    const std::string SEMICOLON = "SEMICOLON";
    const std::string STARTCYCLE = "STARTCYCLE";
    const std::string ENDCYCLE = "ENDCYCLE";
    const std::string STARTIF = "STARTIF";
    const std::string STARTELSE = "STARTELSE";
    const std::string ENDIF = "ENDIF";
    const std::string ENDELSE = "ENDELSE";
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
    const std::string NUMBER = "NUMBER";
    const std::string VARIABLE = "VARIABLE";
}


struct TokenType
{
    std::string name;
    std::string regex;

    TokenType();
    TokenType(const std::string &name, const std::string &regex);
};


#endif //DRUS_JA_TOKENTYPE_H
