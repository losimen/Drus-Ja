// Drus_Ja by losimen 27.11.2022

#include <iostream>
#include <vector>

#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "CodeGenerator.h"


std::string readFile(const char *fName)
{
    std::ifstream t(fName);

    if (!t.is_open())
        throw std::runtime_error("Not found");

    std::string fileBuffer;

    t.seekg(0, std::ios::end);
    fileBuffer.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    fileBuffer.assign((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());

    return fileBuffer;
}


int main()
{
    std::string fileBuffer = readFile("File.txt");

    LexicalAnalyzer lexicalAnalyzer(fileBuffer);
    std::vector<Token> tokens = lexicalAnalyzer.analyze();
    lexicalAnalyzer.printTokens();

    SyntaxAnalyzer syntaxAnalyzer(tokens);
    std::unique_ptr<INode> root = syntaxAnalyzer.parseCode();
    syntaxAnalyzer.printTree(root);

    CodeGenerator codeGenerator;
    codeGenerator.generateCode(root);
    codeGenerator.writeToFile("File.asm");

    system(std::string("masm32\\bin\\ml /c /coff " + std::string("File") + ".asm").c_str());
    system(std::string("masm32\\bin\\Link /SUBSYSTEM:WINDOWS " + std::string("File") + ".obj").c_str());

    return 0;
}
