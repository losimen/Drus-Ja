//
// Created by Павло Коваль on 29.11.2022.
//

#include "LexicalAnalyzer.h"


LexicalAnalyzer::LexicalAnalyzer(): tokenTypeList(TokenTypeList::getTokenTypeList())
{
    pos = 0;
}


bool LexicalAnalyzer::nextToken()
{
    if (pos >= code.length())
        return false;

    Token token;

    std::cout << "---->" << std::endl << code.substr(pos) << "---<" << std::endl;
    for (auto &type: tokenTypeList)
    {
        std::regex self_regex("^" + type.regex, std::regex_constants::ECMAScript | std::regex_constants::icase);
        std::cmatch cm;

        if (std::regex_search(code.substr(pos).c_str(), cm, self_regex))
        {
            token.pos = pos;
            token.value = code.substr(pos, cm.length());

            pos += cm.length();

            token.type = type;

            if (token.type.name == "UNDEFINED")
                return true;

            tokenList.push_back(token);

//            std::cout << "Found token: " << token.type.name << " value:  " << token.value << " pos: " << token.pos << std::endl;

            return true;
        }
    }

    throw std::runtime_error("Undefined token");
}

std::vector<Token> LexicalAnalyzer::analyze(std::string &input)
{
    code = input;

    while (nextToken())
    { }

    return tokenList;
}
