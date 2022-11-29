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

    for (auto &type: tokenTypeList)
    {
        std::regex self_regex("^" + type.regex, std::regex_constants::ECMAScript | std::regex_constants::icase);
        std::cmatch cm;

        if (std::regex_search(code.substr(pos).c_str(), cm, self_regex))
        {
            Token token;

            token.pos = pos;
            token.value = code.substr(pos, cm.length());

            row += cm.length();
            pos += cm.length();

            token.type = type;
            token.line = line;
            token.row = row;

            // std::cout << "Found token: " << token.type.name << " value:  " << token.value << " pos: " << token.pos << std::endl;
            if (token.type.name == "NEWLINE")
            {
                row = 1;
                line++;
                return true;
            }
            else
            {
                tokenList.push_back(token);
                return true;
            }
        }
    }

    throw std::runtime_error("Undefined token");
}

std::vector<Token> LexicalAnalyzer::analyze(std::string &input)
{
    code = input;
    line = 1;
    row = 1;

    while (nextToken())
    { }

    std::cout << "Total amount of lines: " << line << std::endl;
    return tokenList;
}
