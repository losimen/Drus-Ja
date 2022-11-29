//
// Created by Павло Коваль on 29.11.2022.
//

#include "LexicalAnalyzer.h"


LexicalAnalyzer::LexicalAnalyzer(): tokenTypeList(TokenTypeList::getTokenTypeList())
{
    isComment = false;
    line = 1;
    pos = 0;
}


bool LexicalAnalyzer::nextToken()
{
    if (pos >= code.length())
        return false;

    // If comment is started, skip all characters until comment is ended
    if (isComment)
    {
        Token token;

        token.line = line;
        unsigned oldPos = pos;

        while (code[pos] != '\n')
        {
            if (code[pos] == '*' && code[pos + 1] == '/')
            {
                isComment = false;
                pos += 2;

                token.line = line;
                token.pos = oldPos;
                token.type = TokenTypeList::getTokenType(TokenTypes::ENDCOMMENT);
                token.value = code.substr(oldPos, pos - oldPos);

                tokenList.push_back(token);
                break;
            }

            if (pos >= code.length())
                return false;

            pos++;
        }
        line++;
        pos++;

        return true;
    }

    // Check line for tokens
    for (auto &type: tokenTypeList)
    {
        std::regex selfRegex("^" + type.regex, std::regex_constants::ECMAScript | std::regex_constants::icase);
        std::cmatch cm;

        if (std::regex_search(code.substr(pos).c_str(), cm, selfRegex))
        {
            Token token;

            token.pos = pos;
            token.type = type;
            token.line = line;
            token.row = row;
            token.value = code.substr(pos, cm.length());

            pos += cm.length();

            // std::cout << "Found token: " << token.type.name << " value:  " << token.value << " pos: " << token.pos << std::endl;
            if (token.type.name == TokenTypes::NEWLINE)
            {
                row = 1;
                line++;
            }
            else if (token.type.name == TokenTypes::STARTCOMMENT)
            {
                isComment = true;
                tokenList.push_back(token);
            }
            else if (token.type.name == TokenTypes::SPACE)
            {
                pos++;
            }
            else
            {
                tokenList.push_back(token);
            }

            return true;
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
    {
        auto token = tokenList.end() - 1;

//        std::cout << token->type.name << std::endl;
    }

    std::cout << "Total amount of lines: " << line << std::endl;
    return tokenList;
}
