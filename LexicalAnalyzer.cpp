//
// Created by Павло Коваль on 29.11.2022.
//

#include "LexicalAnalyzer.h"


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

    std::string subCode = code.substr(pos);
    for (auto &type: tokenTypeList)
    {
        std::regex selfRegex("^" + type.regex, std::regex_constants::ECMAScript | std::regex_constants::icase);
        std::smatch sm;

        if (std::regex_search(subCode, sm, selfRegex))
        {
            /* TODO: fix bag?
             * ^[1-9]* matches words and digits somehow??
             * when ^[1-9]* receives string with letters |=> sm.length() = 0;
             *
             *    TRY THIS CODE:
             --------- start code -----
             std::string reg= "^[1-9]*";
             std::string code = "ggg";

             std::regex selfRegex(reg, std::regex_constants::ECMAScript | std::regex_constants::icase);
             std::smatch sm;

             if (std::regex_search(code, sm, selfRegex))
             {
             std::cout << "found: " << sm.str() << std::endl;
             std::cout << "number: " << sm.str().length() << std::endl;
             }
             --------- end code ----
             * it works in opposite way with ^[a-z]*
             */
            if (sm.length() == 0)
                continue;

            Token token;

            token.pos = pos;
            token.type = type;
            token.line = line;
            token.row = row;
            token.value = code.substr(pos, sm.length());

            pos += sm.length();

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
                // Do nothing
            }
            else
            {
                tokenList.push_back(token);
            }

            return true;
        }
    }

    throw std::runtime_error("Undefined token " + std::string(1, code[pos]) +  " at " + std::to_string(line) + " line");
}


LexicalAnalyzer::LexicalAnalyzer(const std::string &code): tokenTypeList(TokenTypeList::getTokenTypeList())
{
    this->code = code;
    isComment = false;
    line = 1;
    pos = 0;
}


std::vector<Token> LexicalAnalyzer::analyze()
{
    line = 1;
    row = 1;

    while (nextToken())
    {
        // For logging:
        // auto token = tokenList.end() - 1;
        // std::cout << token->type.name << std::endl;
    }

    std::cout << "Total amount of lines: " << line << std::endl;
    return tokenList;
}
