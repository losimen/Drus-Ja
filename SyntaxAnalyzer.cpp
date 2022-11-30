//
// Created by Павло Коваль on 30.11.2022.
//

#include "SyntaxAnalyzer.h"

SyntaxAnalyzer::SyntaxAnalyzer(std::vector<Token> &tokens): tokens(tokens)
{

}


Token SyntaxAnalyzer::match()
{
    return Token();
}


Token SyntaxAnalyzer::require()
{
    return Token();
}

