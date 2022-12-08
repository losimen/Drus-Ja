// Drus_Ja by losimen 04.12.2022

#ifndef DRUS_JA_CODEGENERATOR_H
#define DRUS_JA_CODEGENERATOR_H

// TODO: remove iostream
#include <iostream>

#include <vector>
#include <string>
#include <fstream>

#include "AST/ASTFactory.h"


enum class Sections
{
    DATA,
    CODE
};


enum class ConditionLogic
{
    AND,
    OR,
    UNDEFINED
};


class CodeGenerator
{
private:
    unsigned ifCounter;
    unsigned forCounter;

    std::vector<std::string> m_code;
    std::vector<std::string>::iterator m_codeIterator;

    void generateHeader();
    void generateCodeNode(std::unique_ptr<INode> &node);
    void generateCodeCondition(std::unique_ptr<INode> &node, unsigned currentIfCounter, ConditionLogic logic);

    void addLineToSection(const std::string &line, Sections section);
    void addTextToLastLine(const std::string &text);

public:
    CodeGenerator();
    void generateCode(std::unique_ptr<INode> &root);
    void writeToFile(const std::string& filename);

};


#endif //DRUS_JA_CODEGENERATOR_H
