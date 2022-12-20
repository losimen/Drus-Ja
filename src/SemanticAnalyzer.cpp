// Drus_Ja by losimen 04.12.2022
#include "SemanticAnalyzer.h"

void SemanticAnalyzer::addVariable(const std::string &variable)
{
    variables.push_back(variable);
}


bool SemanticAnalyzer::isVariable(const std::string &variable)
{
    auto isInList = std::find_if(variables.begin(), variables.end(),
                                 [&variable](const std::string &str)
                                 {
                                     return variable == str;
                                 });

    return isInList != variables.end();
}
