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
    auto root = ASTFactory::createStatementNode();
    auto rootCasted = dynamic_cast<StatementNode *>(root.get());

    if (tokens.empty())
        return root;

    // check if program name and var block is present
    if (tokens[0].type.name == TokenTypes::PROGRAM)
    {
        pos++;
        Token programName = require({TokenTypes::VARIABLE});
        rootCasted->nodes.push_back(ASTFactory::createProgramNameNode(programName));
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
            // check whether start block is present
            if (match({TokenTypes::START}).type.name == TokenTypes::START)
            {
                require({TokenTypes::SEMICOLON});
                isStart = !isStart;
                continue;
            }

            codeStringNode = parseVariableBlock();
            require({TokenTypes::SEMICOLON});
        }
        else if (isVar && isStart && !isFinish)
        {
            // check whether end of program
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

        rootCasted->add(codeStringNode);
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
    // Parse unary operations
    if (match({TokenTypes::INPUT, TokenTypes::OUTPUT,
               TokenTypes::STARTCYCLE, TokenTypes::STARTIF}).type.name != TokenTypes::UNDEFINED)
    {
        pos -= 1;

        // Parse input/output statement
        auto io = match({TokenTypes::INPUT, TokenTypes::OUTPUT});
        if (io.type.name != TokenTypes::UNDEFINED)
        {
            auto operand = parseVariableOrNumber();
            return ASTFactory::createUnarOperationNode(io, operand);
        }

        // Parse for loop statement
        auto stCycle = match({TokenTypes::STARTCYCLE});
        if (stCycle.type.name != TokenTypes::UNDEFINED)
        {
            auto root = ASTFactory::createForNode();
            auto rootCasted = dynamic_cast<ForNode*>(root.get());

            rootCasted->stValue = parseVariableOrNumber();
            require({TokenTypes::SEMICOLON});

            while (tokens[pos].type.name != TokenTypes::ENDCYCLE)
            {
                if (pos > tokens.size())
                    throw std::runtime_error("Syntax error undefined cycle");

                auto codeStringNode = parseMainBlock();
                require({TokenTypes::SEMICOLON});
                rootCasted->add(codeStringNode);
            }

            // root assign...
            auto ndCycle = match({TokenTypes::ENDCYCLE});
            rootCasted->ndValue = parseVariableOrNumber();

            return root;
        }

        // Parse if statement
//        auto stIf = match({TokenTypes::STARTIF});
//        if (stIf.type.name != TokenTypes::UNDEFINED)
//        {
//            auto root = ASTFactory::createIfNode();
//            auto rootCasted = dynamic_cast<IfNode*>(root.get());
//
//            rootCasted->condition = parseCondition();
//
//            while (tokens[pos].type.name != TokenTypes::ENDIF)
//            {
//                if (pos > tokens.size())
//                    throw std::runtime_error("Syntax error undefined if");
//
//                auto codeStringNode = parseMainBlock();
//                require({TokenTypes::SEMICOLON});
//                rootCasted->add(codeStringNode);
//            }
//
//            // root assign...
//            auto ndIf = match({TokenTypes::ENDIF});
//            return root;
//        }
    }

    // Parse assignment statement
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
    {
        if (semanticAnalyzer.isVariable(variable.value))
            return ASTFactory::createVariableNode(variable);
        else
            throw std::runtime_error("Syntax error " + std::to_string(variable.line) + ": variable " + variable.value + " is not declared");
    }

    throw std::runtime_error("Syntax error: " + std::to_string(tokens[pos].line) + ": expected variable or number");
}


std::unique_ptr<INode> SyntaxAnalyzer::parseVariableBlock()
{
    std::unique_ptr<INode> codeStringNode;

    if (match({TokenTypes::DATATYPE}).type.name == TokenTypes::UNDEFINED)
        throw std::runtime_error("Syntax error: " + std::to_string(tokens[pos].line) + " |p: " +
                                 std::to_string(tokens[pos].pos) + ": expected data type");

    Token variable = match({TokenTypes::VARIABLE});
    if (variable.type.name == TokenTypes::UNDEFINED)
        throw std::runtime_error("Syntax error: " + std::to_string(variable.line) + " |p: " +
                                 std::to_string(variable.pos) + ": expected variable name");

    if (semanticAnalyzer.isVariable(variable.value))
        throw std::runtime_error("Syntax error: " + std::to_string(variable.line) + " |p: " +
                                 std::to_string(variable.pos) + ": variable " + variable.value + " is already declared");

    semanticAnalyzer.addVariable(variable.value);
    codeStringNode = parseVariableOrNumber();

    return ASTFactory::createInitVariableNode(variable, codeStringNode);
}
