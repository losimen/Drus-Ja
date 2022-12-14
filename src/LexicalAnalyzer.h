// Drus_Ja by losimen 29.11.2022

#ifndef DRUS_JA_LEXICALANALYZER_H
#define DRUS_JA_LEXICALANALYZER_H


#include <fstream>
#include <regex>
#include <string>
#include <algorithm>
#include <iomanip>

#include "Token.h"
#include "TokenTypeList.h"


class LexicalAnalyzer
{
private:
    std::vector<TokenType> &tokenTypeList;

    bool isComment;

    unsigned line;
    unsigned pos;
    unsigned row;

    std::string code;
    std::vector<Token> tokenList;

    bool nextToken();

public:
    LexicalAnalyzer() = delete;
    LexicalAnalyzer(const std::string &code);

    void printTokens();

    std::vector<Token> analyze();
};


#endif //DRUS_JA_LEXICALANALYZER_H
