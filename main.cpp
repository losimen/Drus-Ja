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
        static int forCounter = 0;
        forCounter++;
        std::cout << "---FOR- " << forCounter << std::endl;

        printTreeElem(pForNode->stValue);
        printTree(node);

        std::cout << "---END FOR " << forCounter;
        printTreeElem(pForNode->ndValue);
    }
    else if (auto pIfNode = dynamic_cast<IfNode*>(node.get()))
    {
        static int ifCounter = 0;
        ifCounter++;

        std::cout << "---IF " << ifCounter << " ";
        printTreeElem(pIfNode->condition);
        std::cout << std::endl;

        printTree(pIfNode->ifBody);

        if (auto pElseBody = dynamic_cast<ElseBodyNode*>(pIfNode->elseBody.get()))
        {
            if (!pElseBody->nodes.empty())
            {
                std::cout << "---ELSE " << ifCounter << " " << std::endl;
                printTree(pIfNode->elseBody);
            }
        }

        std::cout << "---END IF " << ifCounter << std::endl;
    }
}


void printTree(std::unique_ptr<INode> &root)
{
    auto iBlock = dynamic_cast<IBlockNode*>(root.get());

    if (iBlock == nullptr)
        throw std::runtime_error("iBlock == nullptr");

    for (auto &node : iBlock->nodes)
    {
        printTreeElem(node);
        std::cout << std::endl;
    }
}


int main()
{
    std::string fileBuffer = readFile("File.txt");

    LexicalAnalyzer lexicalAnalyzer(fileBuffer);
    std::vector<Token> tokens = lexicalAnalyzer.analyze();
    lexicalAnalyzer.printTokens();

    SyntaxAnalyzer syntaxAnalyzer(tokens);
    std::unique_ptr<INode> root = syntaxAnalyzer.parseCode();
    printTree(root);

    CodeGenerator codeGenerator;
    codeGenerator.generateCode(root);
    codeGenerator.writeToFile("File.asm");

    return 0;
}
