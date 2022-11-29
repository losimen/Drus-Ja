//
// Created by Павло Коваль on 29.11.2022.
//

#ifndef DRUS_JA_LEXICALANALYZER_H
#define DRUS_JA_LEXICALANALYZER_H

// TODO: remove iostream
#include <iostream>
#include <regex>
#include <string>

#include "Token.h"
#include "TokenTypeList.h"


class LexicalAnalyzer
{
private:
    std::vector<TokenType> &tokenTypeList;

    unsigned line;
    unsigned pos;
    unsigned row;

    std::string code;
    std::vector<Token> tokenList;

    bool nextToken();
public:
    LexicalAnalyzer();

    std::vector<Token> analyze(std::string &input);
};


#endif //DRUS_JA_LEXICALANALYZER_H
