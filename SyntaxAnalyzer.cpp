// Drus_Ja by losimen 29.11.2022

#include "SyntaxAnalyzer.h"


SyntaxAnalyzer::SyntaxAnalyzer(std::vector<Token> &tokens): tokens(tokens)
{

}


Token SyntaxAnalyzer::match(std::initializer_list<std::string> expected)
{
    if (pos < tokens.size())
    {
        const auto &token = tokens[pos];

        if (std::find_if(expected.begin(), expected.end(), [&token](const std::string &str)
                                                           { return token.type.name == str; }) != expected.end())
        {
            pos++;
            return token;
        }
    }

    return Token();
}


Token SyntaxAnalyzer::require(std::initializer_list<std::string> expected)
{
    Token token = match(expected);

    if (token.type.name == TokenTypes::UNDEFINED)
        throw std::runtime_error("Syntax error " + std::to_string(token.line) + " |p: " +
                                 std::to_string(token.pos) + ": expected " + *expected.begin());

    return token;
}


std::unique_ptr<INode> SyntaxAnalyzer::parseCode()
{
    std::unique_ptr<INode> root = ASTFactory::createStatementNode();
    StatementNode *child = dynamic_cast<StatementNode *>(root.get());

    if (tokens.empty())
        return root;

    // check if program name and var block is present
    if (tokens[0].type.name == TokenTypes::PROGRAM)
    {
        pos++;
        Token programName = require({TokenTypes::VARIABLE});
        child->nodes.push_back(ASTFactory::createProgramNameNode(programName));
        require({TokenTypes::SEMICOLON});

        require({TokenTypes::VARBLOCK});
        require({TokenTypes::SEMICOLON});
        isVar = true;
    }

    while (pos < tokens.size() && !isFinish)
    {
        std::unique_ptr<INode> codeStringNode;

        if (isVar && !isStart && !isFinish)
        {
            // parsing variable declaration
            if (match({TokenTypes::START}).type.name == TokenTypes::START)
            {
                require({TokenTypes::SEMICOLON});
                isStart = !isStart;
                continue;
            }

            if (match({TokenTypes::DATATYPE}).type.name == TokenTypes::UNDEFINED)
                throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + " |p: " +
                                         std::to_string(tokens[pos].pos) + ": expected data type");

            Token variable = match({TokenTypes::VARIABLE});
            if (variable.type.name == TokenTypes::UNDEFINED)
                throw std::runtime_error("Syntax error " + std::to_string(variable.line) + " |p: " +
                                         std::to_string(variable.pos) + ": expected variable name");

            codeStringNode = parseVariableOrNumber();
            codeStringNode = ASTFactory::createInitVariableNode(variable, codeStringNode);
            require({TokenTypes::SEMICOLON});
        }
        else if (isVar && isStart && !isFinish)
        {
            // parsing main block
            if (match({TokenTypes::FINISH}).type.name == TokenTypes::FINISH)
            {
                require({TokenTypes::SEMICOLON});
                isFinish = !isFinish;
                continue;
            }

            codeStringNode = parseMainBlock();
            require({TokenTypes::SEMICOLON});
        }
        else
        {
            throw std::runtime_error("Syntax error: invalid program structure");
        }

        child->add(codeStringNode);
    }

    if (isFinish)
    {
        return root;
    }
    else
    {
        throw std::runtime_error("Syntax error: expected finish");
    }
}


std::unique_ptr<INode> SyntaxAnalyzer::parseMainBlock()
{
    if (match({TokenTypes::VARIABLE}).type.name == TokenTypes::UNDEFINED)
        // TODO: parse print, read, for
        throw std::runtime_error("NOT READY");
    pos -= 1;

    auto variableNode = parseVariableOrNumber();
    const auto assignOperator = match({TokenTypes::ASSIGNMENT});
    if (assignOperator.type.name != TokenTypes::UNDEFINED)
    {
        auto rightFormulaNode = parseFormula();
        auto binaryOperatorNode = ASTFactory::createBinOperationNode(assignOperator, variableNode, rightFormulaNode);
        return binaryOperatorNode;
    }

    throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + ": expected expression");
}


std::unique_ptr<INode> SyntaxAnalyzer::parseFormula()
{
    auto leftNode = parseParenthesis();

    Token op = match({TokenTypes::PLUS, TokenTypes::MINUS, TokenTypes::MULTIPLY, TokenTypes::DIVIDE});
    while (op.type.name != TokenTypes::UNDEFINED)
    {
        auto rightNode = parseParenthesis();
        leftNode = ASTFactory::createBinOperationNode(op, leftNode, rightNode);
        op = match({TokenTypes::PLUS, TokenTypes::MINUS, TokenTypes::MULTIPLY, TokenTypes::DIVIDE});
    }

    return leftNode;
}


std::unique_ptr<INode> SyntaxAnalyzer::parseParenthesis()
{
    if (match({TokenTypes::LPAREN}).type.name != TokenTypes::UNDEFINED)
    {
        auto node = parseFormula();
        require({TokenTypes::RPAREN});
        return node;
    }

    return parseVariableOrNumber();
}


std::unique_ptr<INode> SyntaxAnalyzer::parseVariableOrNumber()
{
    const auto number = match({TokenTypes::NUMBER});
    if (number.type.name != TokenTypes::UNDEFINED)
        return ASTFactory::createNumberNode(number);

    const auto variable = match({TokenTypes::VARIABLE});
    if (variable.type.name != TokenTypes::UNDEFINED)
        return ASTFactory::createVariableNode(variable);

    throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + ": expected variable or number");
}


std::unique_ptr<INode> SyntaxAnalyzer::parseVariable()
{
    const auto variable = match({TokenTypes::VARIABLE});
    if (variable.type.name != TokenTypes::UNDEFINED)
        return ASTFactory::createVariableNode(variable);

    throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + ": expected variable");
}


std::unique_ptr<INode> SyntaxAnalyzer::parseNumber()
{
    const auto number = match({TokenTypes::NUMBER});
    if (number.type.name != TokenTypes::UNDEFINED)
        return ASTFactory::createNumberNode(number);

    throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + ": expected number");
}


void SyntaxAnalyzer::setFlags()
{
    if (tokens[pos].type.name == TokenTypes::PROGRAM)
    {
        isProgram = !isProgram;
        pos += 1;
    }
    else if (tokens[pos].type.name == TokenTypes::VARBLOCK)
    {
        isVar = !isVar;
        pos += 1;
    }
    else if (tokens[pos].type.name == TokenTypes::START)
    {
        isStart = !isStart;
        pos += 1;
    }
    else if (tokens[pos].type.name == TokenTypes::FINISH)
    {
        isFinish = !isFinish;
        pos += 1;
    }
}
