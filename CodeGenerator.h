// Drus_Ja by losimen 04.12.2022

#ifndef DRUS_JA_CODEGENERATOR_H
#define DRUS_JA_CODEGENERATOR_H

#include <vector>
#include <string>
#include <fstream>


class CodeGenerator
{
private:
    std::vector<std::string> m_code;

    void generateHeader();

public:
    CodeGenerator();
    void writeToFile(const std::string& filename);

};


#endif //DRUS_JA_CODEGENERATOR_H
