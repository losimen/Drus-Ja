// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_SYNTAXANALYZER_H
#define DRUS_JA_SYNTAXANALYZER_H

// TODO:remove iostream
#include <iostream>

#include "Token.h"

#include "AST/StatementNode.h"
#include "AST/VariableNode.h"
#include "AST/NumberNode.h"
#include "AST/BinOperationNode.h"
#include "AST/UnarOperationNode.h"


class SyntaxAnalyzer
{
private:
    std::vector<Token> &tokens;
    unsigned pos;

    Token match(std::initializer_list<std::string> expected);
    Token require(std::initializer_list<std::string> expected);

    INode parseExpression();
    INode parseFormula();
    INode parseVariableOrNumber();
    INode parseParenthesis();

public:
    SyntaxAnalyzer() = delete;
    SyntaxAnalyzer(std::vector<Token> &tokens);

    StatementNode parseCode();
};


#endif //DRUS_JA_SYNTAXANALYZER_H
