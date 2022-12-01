// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_SYNTAXANALYZER_H
#define DRUS_JA_SYNTAXANALYZER_H

// TODO:remove iostream
#include <iostream>

#include "Token.h"
#include "AST/ASTFactory.h"


class SyntaxAnalyzer
{
private:
    std::vector<Token> &tokens;
    unsigned pos;

    Token match(std::initializer_list<std::string> expected);
    Token require(std::initializer_list<std::string> expected);

    std::unique_ptr<INode> parseExpression();
    std::unique_ptr<INode> parseFormula();
    std::unique_ptr<INode> parseVariableOrNumber();
    std::unique_ptr<INode> parseParenthesis();

public:
    SyntaxAnalyzer() = delete;
    SyntaxAnalyzer(std::vector<Token> &tokens);

    std::unique_ptr<INode> parseCode();
};


#endif //DRUS_JA_SYNTAXANALYZER_H
