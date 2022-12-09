// Drus_Ja by losimen 27.11.2022

#include <iostream>
#include <vector>

#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "CodeGenerator.h"


// Read all file content into single std::string
std::string readFile(const std::string &fName)
{
    std::ifstream t(fName);

    if (!t.is_open())
        return std::string();

    std::string fileBuffer;

    t.seekg(0, std::ios::end);
    fileBuffer.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    fileBuffer.assign((std::istreambuf_iterator<char>(t)),
                      std::istreambuf_iterator<char>());

    t.close();
    return fileBuffer;
}


void writeErrorFile(const std::string &what)
{
    static const std::string errorFileName = "errors.txt";
    std::ofstream file;
    file.open(errorFileName, std::ios::app);

    if (!file.is_open())
    {
        throw std::runtime_error("Error in opening file - " + errorFileName);
    }

    file << what;
    file.close();
}



int main(int argc, char* argv[])
{
    // get file name
    std::string fileName;

    if (argc != 2)
    {
        std::cout << "Input file name: ";
        std::cin >> fileName;
    }
    else
    {
        fileName = argv[1];
    }
    fileName += ".k09";

    std::string fileBuffer = readFile(fileName);
    if (fileBuffer.empty())
    {
        std::string errStr = "File with name: " + fileName + " doesn't exist";
        std::cerr << errStr << std::endl;
        writeErrorFile(errStr);
        return -1;
    }

    // compilation process
    try
    {
        LexicalAnalyzer lexicalAnalyzer(fileBuffer);
        std::vector<Token> tokens = lexicalAnalyzer.analyze();
        lexicalAnalyzer.printTokens();

        SyntaxAnalyzer syntaxAnalyzer(tokens);
        std::unique_ptr<INode> root = syntaxAnalyzer.parseCode();
        syntaxAnalyzer.printTree(root);

        CodeGenerator codeGenerator;
        codeGenerator.generateCode(root);
        codeGenerator.writeToFile("File.asm");
    }
    catch (std::exception& err)
    {
        std::cerr << err.what() << std::endl;
        writeErrorFile(err.what());
        return -1;
    }

    // system(std::string("C:\\masm32\\bin\\ml /c /coff " + std::string("File") + ".asm").c_str());
    // system(std::string("C:\\masm32\\bin\\Link /SUBSYSTEM:WINDOWS " + std::string("File") + ".obj").c_str());

    return 0;
}
