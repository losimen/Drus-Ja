// Drus_Ja by losimen 27.11.2022

#include <iostream>
#include <vector>

#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "CodeGenerator.h"


void printTree(std::unique_ptr<INode> &root);


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

    if (auto *pBinOperationNode = dynamic_cast<BinOperationNode*>(node.get()))
    {
        if (pBinOperationNode->op.type.name == TokenTypes::ASSIGNMENT)
        {
            printTreeElem(pBinOperationNode->leftOperand);
            std::cout << pBinOperationNode->op.type.name << " ";
            printTreeElem(pBinOperationNode->rightOperand);
            return;
        }

        std::cout << "( ";
        printTreeElem(pBinOperationNode->leftOperand);
        std::cout << pBinOperationNode->op.type.name << " ";
        printTreeElem(pBinOperationNode->rightOperand);
        std::cout << " ) ";
    }
    else if (auto pUnarOperationNode = dynamic_cast<UnarOperationNode*>(node.get()))
    {
        std::cout << pUnarOperationNode->op.type.name << " ";
        printTreeElem(pUnarOperationNode->operand);
    }
    else if (auto pProgramNameNode = dynamic_cast<ProgramNameNode*>(node.get()))
    {
        std::cout << "Program name: " << pProgramNameNode->programName.value;
    }
    else if (auto pNumberNode = dynamic_cast<NumberNode*>(node.get()))
    {
        std::cout << pNumberNode->number.value << " ";
    }
    else if (auto pVariableNode = dynamic_cast<VariableNode*>(node.get()))
    {
        std::cout << pVariableNode->variable.value << " ";
    }
    else if (auto pInitVariableNode = dynamic_cast<InitVariableNode*>(node.get()))
    {
        std::cout << "INTEGER " << pInitVariableNode->token.value << " = ";
        printTreeElem(pInitVariableNode->value);
    }
    else if (auto pForNode = dynamic_cast<ForNode*>(node.get()))
    {
        std::cout << "Start for ";
        printTreeElem(pForNode->stValue);
        std::cout << std::endl;

        printTree(node);

        std::cout << "End for ";
        printTreeElem(pForNode->ndValue);
    }
}


void printTree(std::unique_ptr<INode> &root)
{
    if (auto child = dynamic_cast<StatementNode*>(root.get()))
    {
        for (auto &node : child->nodes)
        {
            printTreeElem(node);
            std::cout << std::endl;
        }
    }

    if (auto child = dynamic_cast<ForNode*>(root.get()))
    {
        for (auto &node : child->nodes)
        {
            printTreeElem(node);
            std::cout << std::endl;
        }
    }
}


int main()
{
    std::string fileBuffer = readFile("File.txt");

    LexicalAnalyzer lexicalAnalyzer(fileBuffer);
    std::vector<Token> tokens = lexicalAnalyzer.analyze();

//    for (auto &token: tokens)
//        std::cout << "L: " << token.line << " |TYPE: " << token.type.name << " | " << token.value << std::endl;

    SyntaxAnalyzer syntaxAnalyzer(tokens);
    std::unique_ptr<INode> root = syntaxAnalyzer.parseCode();
    printTree(root);

    CodeGenerator codeGenerator;
    codeGenerator.generateCode(root);
    codeGenerator.writeToFile("File.asm");

    return 0;
}
