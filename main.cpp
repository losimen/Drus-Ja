#include <iostream>
#include <vector>
#include <fstream>
#include <regex>

#include "TokenTypeList.h"
#include "LexicalAnalyzer.h"


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
    std::string fileBuffer = readFile("File.txt");

    TokenList &tokenTypeList = TokenTypeList::getTokenTypeList();
//    for (auto &i : tokenTypeList)
//    {
//        std::cout << i.first << " " << i.second.name << std::endl;
//    }


    LexicalAnalyzer lexicalAnalyzer;
    std::vector<Token> tokens = lexicalAnalyzer.analyze(fileBuffer);

    for (auto &token: tokens)
        std::cout << "L: " << token.line << "[" << token.row << "]" << " |TYPE: " << token.type.name << " | " << token.value << std::endl;

    return 0;
}
