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
        throw std::runtime_error("Syntax error " + std::to_string(token.line) + ": expected " + *expected.begin());

    return token;
}

StatementNode SyntaxAnalyzer::parseCode()
{
    auto root = StatementNode();

    while (pos < tokens.size())
    {
        const auto codeStringNode = parseExpression();
        require({TokenTypes::SEMICOLON});
        root.add(codeStringNode);
    }

    return root;
}

INode SyntaxAnalyzer::parseExpression()
{
    if (match({TokenTypes::VARIABLE}).type.name == TokenTypes::UNDEFINED)
        throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + ": expected expression");

    pos -= 1;

    auto variableNode = parseVariableOrNumber();
    const auto assignOperator = match({TokenTypes::ASSIGNMENT});
    if (assignOperator.type.name != TokenTypes::UNDEFINED)
    {
        const auto rightFormulaNode = parseFormula();
        const auto binaryOperatorNode = BinOperationNode(assignOperator, variableNode, rightFormulaNode);
        return binaryOperatorNode;
    }

    throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + ": expected expression");
}


INode SyntaxAnalyzer::parseFormula()
{
    auto leftNode = parseParenthesis();
    auto op = match({TokenTypes::PLUS, TokenTypes::MINUS, TokenTypes::MULTIPLY, TokenTypes::DIVIDE});
    if (op.type.name != TokenTypes::UNDEFINED)
    {
        const auto rightNode = parseParenthesis();
        leftNode = BinOperationNode(op, leftNode, rightNode);
        op = match({TokenTypes::PLUS, TokenTypes::MINUS, TokenTypes::MULTIPLY, TokenTypes::DIVIDE});
    }

    return leftNode;
}


INode SyntaxAnalyzer::parseVariableOrNumber()
{
    const auto number = match({TokenTypes::NUMBER});
    if (number.type.name != TokenTypes::UNDEFINED)
        return NumberNode(number);

    const auto variable = match({TokenTypes::VARIABLE});
    if (variable.type.name != TokenTypes::UNDEFINED)
        return VariableNode(variable);

    throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + ": expected variable or number");
}

INode SyntaxAnalyzer::parseParenthesis()
{
    if (match({TokenTypes::LPAREN}).type.name != TokenTypes::UNDEFINED)
    {
        const auto node = parseFormula();
        require({TokenTypes::RPAREN});
        return node;
    }

    return parseVariableOrNumber();
}

