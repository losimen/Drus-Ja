// Drus_Ja by losimen 27.11.2022

#include <iostream>
#include <vector>
#include <fstream>

#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"


std::string readFile(const char *fName)
{
    std::ifstream t(fName);
    std::string fileBuffer;

    t.seekg(0, std::ios::end);
    fileBuffer.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    fileBuffer.assign((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());

    return fileBuffer;
}


void printTreeElem(std::unique_ptr<INode> &node)
{
    if (node == nullptr)
    {
        std::cout << "nullptr" << std::endl;
        return;
    }

    if (BinOperationNode *pBinOperationNode = dynamic_cast<BinOperationNode*>(node.get()))
    {
        if (pBinOperationNode->op.type.name == TokenTypes::ASSIGNMENT)
        {
            printTreeElem(pBinOperationNode->leftOperand);
            std::cout << pBinOperationNode->op.type.name << " ";
            printTreeElem(pBinOperationNode->rightOperand);
            return;
        }

        printTreeElem(pBinOperationNode->leftOperand);
        std::cout << pBinOperationNode->op.type.name << " ";
        printTreeElem(pBinOperationNode->rightOperand);
    }
    else if (ProgramNameNode *pProgramNameNode = dynamic_cast<ProgramNameNode*>(node.get()))
    {
        std::cout << "Program name: " << pProgramNameNode->programName.value << std::endl;
    }
    else if (NumberNode *pNumberNode = dynamic_cast<NumberNode*>(node.get()))
    {
        std::cout << pNumberNode->number.value << " ";
    }
    else if (VariableNode *pVariableNode = dynamic_cast<VariableNode*>(node.get()))
    {
        std::cout << pVariableNode->variable.value << " ";
    }
}


int main() {
    // TODO: add negative numbers
    std::string fileBuffer = readFile("File.txt");

    LexicalAnalyzer lexicalAnalyzer(fileBuffer);
    std::vector<Token> tokens = lexicalAnalyzer.analyze();

//    for (auto &token: tokens)
//        std::cout << "L: " << token.line << " |TYPE: " << token.type.name << " | " << token.value << std::endl;

    SyntaxAnalyzer syntaxAnalyzer(tokens);
    std::unique_ptr<INode> root = syntaxAnalyzer.parseCode();
    StatementNode *child = dynamic_cast<StatementNode *>(root.get());

    for (auto &node: child->nodes)
        printTreeElem(node);

    return 0;
}
