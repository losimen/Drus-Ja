// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_SYNTAXANALYZER_H
#define DRUS_JA_SYNTAXANALYZER_H

#include "Token.h"

#include "AST/StatementNode.h"
#include "AST/VariableNode.h"
#include "AST/NumberNode.h"
#include "AST/UnarOperationNode.h"


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
