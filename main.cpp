#include <iostream>
#include <vector>
#include <fstream>


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

//    LexicalAnalyzer lexicalAnalyzer(fileBuffer);
//    lexicalAnalyzer.doLexicalAnalysis();

    return 0;
}
