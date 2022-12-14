// Drus_Ja by losimen 29.11.2022

#include "SyntaxAnalyzer.h"
#include <iostream>

SyntaxAnalyzer::SyntaxAnalyzer(std::vector<Token> &tokens): tokens(tokens)
{
    pos = 0;
    isStart = false;
    isFinish = false;
    isVar = false;
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

    return {};
}


Token SyntaxAnalyzer::require(std::initializer_list<std::string> expected)
{
    Token token = match(expected);

    if (token.type.name == TokenTypes::UNDEFINED)
        throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + " |p: " +
                                 std::to_string(tokens[pos].pos) + ": expected " + *expected.begin());

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
            require({TokenTypes::SEMICOLON, TokenTypes::NOT});
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
            auto operand = parseExpression();
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
        auto stIf = match({TokenTypes::STARTIF});
        if (stIf.type.name != TokenTypes::UNDEFINED)
        {
            bool isElse = false;
            auto root = ASTFactory::createIfNode();
            auto rootCasted = dynamic_cast<IfNode*>(root.get());

            auto ifBody = ASTFactory::createIfBodyNode();
            auto ifBodyCasted = dynamic_cast<IfBodyNode*>(ifBody.get());

            auto elseBody = ASTFactory::createElseBodyNode();
            auto elseBodyCasted = dynamic_cast<ElseBodyNode*>(elseBody.get());

            require({TokenTypes::LPAREN});
            rootCasted->condition = parseExpression();
            require({TokenTypes::RPAREN});

            rootCasted->ifBody = std::move(ifBody);
            rootCasted->elseBody = std::move(elseBody);
            require({TokenTypes::SEMICOLON});

            while (tokens[pos].type.name != TokenTypes::ENDIF)
            {
                if (pos > tokens.size())
                    throw std::runtime_error("Syntax error undefined if");

                auto codeStringNode = parseMainBlock();
                require({TokenTypes::SEMICOLON});

                if (isElse)
                {
                    elseBodyCasted->add(codeStringNode);
                }
                else
                {
                    ifBodyCasted->add(codeStringNode);

                    if (tokens[pos].type.name == TokenTypes::STARTELSE)
                    {
                        isElse = true;
                        pos++;
                        require({TokenTypes::SEMICOLON});
                    }
                }
            }

            // root assign
            auto ndIf = match({TokenTypes::ENDIF});
            return root;
        }
    }

    // Parse assignment statement
    auto variableNode = parseVariableOrNumber();
    const auto assignOperator = match({TokenTypes::ASSIGNMENT});
    if (assignOperator.type.name != TokenTypes::UNDEFINED)
    {
        auto rightFormulaNode = parseExpression();
        auto binaryOperatorNode = ASTFactory::createBinOperationNode(assignOperator, variableNode, rightFormulaNode);
        return binaryOperatorNode;
    }

    throw std::runtime_error("Syntax error " + std::to_string(tokens[pos].line) + ": expected expression");
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
            throw std::runtime_error("Semantic error " + std::to_string(tokens[pos-1].line) + ": variable " + tokens[pos-1].value + " is not declared");
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
        throw std::runtime_error("Syntax error: " + std::to_string(tokens[pos].line) + " |p: " +
                                 std::to_string(tokens[pos].pos) + ": expected variable name");

    if (semanticAnalyzer.isVariable(variable.value))
        throw std::runtime_error("Syntax error: " + std::to_string(tokens[pos].line) + " |p: " +
                                 std::to_string(tokens[pos].pos) + ": variable " + tokens[pos].value + " is already declared");

    semanticAnalyzer.addVariable(variable.value);
    codeStringNode = parseVariableOrNumber();

    return ASTFactory::createInitVariableNode(variable, codeStringNode);
}


void SyntaxAnalyzer::printTreeElem(std::unique_ptr<INode>& node)
{
    if (node == nullptr)
    {
        std::cout << "nullptr" << std::endl;
        return;
    }

    if (auto* pBinOperationNode = dynamic_cast<BinOperationNode*>(node.get()))
    {
        if (pBinOperationNode->op.type.name == TokenTypes::ASSIGNMENT)
        {
            printTreeElem(pBinOperationNode->leftOperand);
            std::cout << pBinOperationNode->op.type.name << " ";
            printTreeElem(pBinOperationNode->rightOperand);
            return;
        }

        std::cout << "( ";
        printTreeElem(pBinOperationNode->leftOperand);
        std::cout << pBinOperationNode->op.type.name << " ";
        printTreeElem(pBinOperationNode->rightOperand);
        std::cout << " ) ";
    }
    else if (auto pUnarOperationNode = dynamic_cast<UnarOperationNode*>(node.get()))
    {
        std::cout << pUnarOperationNode->op.type.name << " ";
        printTreeElem(pUnarOperationNode->operand);
    }
    else if (auto pProgramNameNode = dynamic_cast<ProgramNameNode*>(node.get()))
    {
        std::cout << "Program name: " << pProgramNameNode->programName.value;
    }
    else if (auto pNumberNode = dynamic_cast<NumberNode*>(node.get()))
    {
        std::cout << pNumberNode->number.value << " ";
    }
    else if (auto pVariableNode = dynamic_cast<VariableNode*>(node.get()))
    {
        std::cout << pVariableNode->variable.value << " ";
    }
    else if (auto pInitVariableNode = dynamic_cast<InitVariableNode*>(node.get()))
    {
        std::cout << "INTEGER " << pInitVariableNode->token.value << " = ";
        printTreeElem(pInitVariableNode->value);
    }
    else if (auto pForNode = dynamic_cast<ForNode*>(node.get()))
    {
        static int forCounter = 0;
        forCounter++;
        std::cout << "---FOR- " << forCounter << std::endl;

        printTreeElem(pForNode->stValue);
        printTree(node);

        std::cout << "---END FOR " << forCounter;
        printTreeElem(pForNode->ndValue);
    }
    else if (auto pIfNode = dynamic_cast<IfNode*>(node.get()))
    {
        static int ifCounter = 0;
        ifCounter++;

        std::cout << "---IF " << ifCounter << " ";
        printTreeElem(pIfNode->condition);
        std::cout << std::endl;

        printTree(pIfNode->ifBody);

        if (auto pElseBody = dynamic_cast<ElseBodyNode*>(pIfNode->elseBody.get()))
        {
            if (!pElseBody->nodes.empty())
            {
                std::cout << "---ELSE " << ifCounter << " " << std::endl;
                printTree(pIfNode->elseBody);
            }
        }

        std::cout << "---END IF " << ifCounter;
    }
}


void SyntaxAnalyzer::printTree(std::unique_ptr<INode>& root)
{
    auto iBlock = dynamic_cast<IBlockNode*>(root.get());

    if (iBlock == nullptr)
        throw std::runtime_error("iBlock == nullptr");

    for (auto& node : iBlock->nodes)
    {
        printTreeElem(node);
        std::cout << std::endl;
    }
}


std::unique_ptr<INode> SyntaxAnalyzer::parseExpression()
{
    return parseAdditive();
}


std::unique_ptr<INode> SyntaxAnalyzer::parseAdditive()
{
    auto result = parseMultiplicative();


    while (true)
    {
        if (parseSingleAdditive(TokenTypes::PLUS, result) || parseSingleAdditive(TokenTypes::MINUS, result) ||
            parseSingleAdditive(TokenTypes::EQUAL, result) ||  parseSingleAdditive(TokenTypes::NOTEQUAL, result) ||
            parseSingleAdditive(TokenTypes::AND, result) || parseSingleAdditive(TokenTypes::OR, result) ||
            parseSingleAdditive(TokenTypes::GREATER, result) || parseSingleAdditive(TokenTypes::LESS, result))
        {
            continue;
        }

        break;
    }

    return result;
}


std::unique_ptr<INode> SyntaxAnalyzer::parseMultiplicative()
{
    auto result = parseUnary();

    while (true)
    {
        auto mul = match({TokenTypes::MULTIPLY});
        if (mul.type.name != TokenTypes::UNDEFINED)
        {
            auto right = parseUnary();
            result = ASTFactory::createBinOperationNode(mul, result, right);
            continue;
        }

        auto div = match({TokenTypes::DIVIDE});
        if (div.type.name != TokenTypes::UNDEFINED)
        {
            auto right = parseUnary();
            result = ASTFactory::createBinOperationNode(div, result, right);
            continue;
        }

        auto mod = match({TokenTypes::MOD});
        if (mod.type.name != TokenTypes::UNDEFINED)
        {
            auto right = parseUnary();
            result = ASTFactory::createBinOperationNode(mod, result, right);
            continue;
        }
        break;
    }

    return result;
}


std::unique_ptr<INode> SyntaxAnalyzer::parsePrimary()
{
    auto numOrVar = match({TokenTypes::NUMBER, TokenTypes::VARIABLE});
    if (numOrVar.type.name != TokenTypes::UNDEFINED)
    {
        --pos;
        return parseVariableOrNumber();
    }

    auto leftBracket = match({TokenTypes::LPAREN});
    if (leftBracket.type.name != TokenTypes::UNDEFINED)
    {
        auto expr = parseExpression();
        require({TokenTypes::RPAREN});
        return expr;
    }

    throw std::runtime_error("Syntax error at " + std::to_string(tokens[pos].line) + ": unexpected token " + tokens[pos].value);
}


bool SyntaxAnalyzer::parseSingleAdditive(const std::string &additiveName, std::unique_ptr<INode> &result)
{
    auto op = match({additiveName});
    if (op.type.name != TokenTypes::UNDEFINED)
    {
        auto right = parseMultiplicative();
        result = ASTFactory::createBinOperationNode(op, result, right);
        return true;
    }

    return false;
}


std::unique_ptr<INode> SyntaxAnalyzer::parseUnary()
{
    auto minus = match({TokenTypes::MINUS});
    if (minus.type.name != TokenTypes::UNDEFINED)
    {
        auto operand = parsePrimary();
        return ASTFactory::createUnarOperationNode(minus, operand);
    }

    auto notEqual = match({TokenTypes::NOT});
    if (notEqual.type.name != TokenTypes::UNDEFINED)
    {
        auto operand = parsePrimary();
        return ASTFactory::createUnarOperationNode(notEqual, operand);
    }

    return parsePrimary();
}
