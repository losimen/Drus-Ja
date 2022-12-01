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


int main() {
    // TODO: add negative numbers
    std::string fileBuffer = readFile("File.txt");

    LexicalAnalyzer lexicalAnalyzer(fileBuffer);
    std::vector<Token> tokens = lexicalAnalyzer.analyze();

    for (auto &token: tokens)
        std::cout << "L: " << token.line << " |TYPE: " << token.type.name << " | " << token.value << std::endl;

    SyntaxAnalyzer syntaxAnalyzer(tokens);
    StatementNode root = syntaxAnalyzer.parseCode();

    for (auto &node: root.nodes)
    {
        std::cout << root.nodes.size() << std::endl;
    }

    return 0;
}
