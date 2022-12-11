// Drus_Ja by losimen 30.11.2022

#ifndef DRUS_JA_SYNTAXANALYZER_H
#define DRUS_JA_SYNTAXANALYZER_H

#include <algorithm>
#include <exception>
#include <stdexcept>

#include "Token.h"
#include "AST/INode.h"
#include "AST/ASTFactory.h"
#include "SemanticAnalyzer.h"


class SyntaxAnalyzer
{
private:
    SemanticAnalyzer semanticAnalyzer;
    std::vector<Token> &tokens;
    unsigned pos;

    // flags for program structure
    bool isVar;
    bool isStart;
    bool isFinish;

    Token match(std::initializer_list<std::string> expected);
    Token require(std::initializer_list<std::string> expected);

    std::unique_ptr<INode> parseVariableBlock();
    std::unique_ptr<INode> parseMainBlock();
    std::unique_ptr<INode> parseVariableOrNumber();
    std::unique_ptr<INode> parseExpression();
    std::unique_ptr<INode> parseAdditive();
    std::unique_ptr<INode> parseMultiplicative();
    std::unique_ptr<INode> parsePrimary();


    void printTreeElem(std::unique_ptr<INode>& node);

public:
    SyntaxAnalyzer() = delete;

    SyntaxAnalyzer(std::vector<Token> &tokens);

    std::unique_ptr<INode> parseCode();
    void printTree(std::unique_ptr<INode>& root);
};


#endif //DRUS_JA_SYNTAXANALYZER_H
