// Drus_Ja by losimen 29.11.2022

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

Token SyntaxAnalyzer::match(std::initializer_list<TokenType> tokenTyp)
{
    Token token;

    if (pos < tokens.size())
    {
        return token;
    }


    return token;
}

