// Drus_Ja by losimen 04.12.2022

#ifndef DRUS_JA_SEMANTICANALYZER_H
#define DRUS_JA_SEMANTICANALYZER_H

#include <vector>
#include <string>


class SemanticAnalyzer
{
private:
    std::vector<std::string> variables;

public:
    void addVariable(const std::string &variable);
    bool isVariable(const std::string &variable);

};


#endif //DRUS_JA_SEMANTICANALYZER_H
