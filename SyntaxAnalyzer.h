//
// Created by Павло Коваль on 30.11.2022.
//

#ifndef DRUS_JA_SYNTAXANALYZER_H
#define DRUS_JA_SYNTAXANALYZER_H


#include "Token.h"


class SyntaxAnalyzer
{
private:
    std::vector<Token> &tokens;
    unsigned pos;

public:
    SyntaxAnalyzer() = delete;
    SyntaxAnalyzer(std::vector<Token> &tokens);

    Token match();
    Token require();

};


#endif //DRUS_JA_SYNTAXANALYZER_H
