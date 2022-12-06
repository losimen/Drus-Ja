// Drus_Ja by losimen 04.12.2022

#include "CodeGenerator.h"


CodeGenerator::CodeGenerator()
{
    generateHeader();
}


void CodeGenerator::generateHeader()
{
    m_code.emplace_back("; Drus_Ja by losimen");
    m_code.emplace_back(".686");
    m_code.emplace_back(".model flat, stdcall");
    m_code.emplace_back("option casemap: none");
    m_code.emplace_back("");
    m_code.emplace_back("include /masm32/include/user32.inc");
    m_code.emplace_back("include /masm32/include/kernel32.inc");
    m_code.emplace_back("include /masm32/include/masm32.inc");
    m_code.emplace_back("include /masm32/include/msvcrt.inc");
    m_code.emplace_back("");
    m_code.emplace_back("includelib /masm32/lib/user32.lib");
    m_code.emplace_back("includelib /masm32/lib/kernel32.lib");
    m_code.emplace_back("includelib /masm32/lib/masm32.lib");
    m_code.emplace_back("includelib /masm32/lib/msvcrt.lib");
    m_code.emplace_back("");
    m_code.emplace_back(".data");
    m_code.emplace_back("fmt db '%d', 13, 10, 0");
    m_code.emplace_back("buffer db 256 dup(0)");
    m_code.emplace_back(";>--DATA SECTION--<");
    m_code.emplace_back("");
    m_code.emplace_back(".code");
    m_code.emplace_back("");
    m_code.emplace_back("start:");
    m_code.emplace_back(";>--CODE SECTION--<");
    m_code.emplace_back("");
    m_code.emplace_back("push 0");
    m_code.emplace_back("call ExitProcess");
    m_code.emplace_back("end start");
}


void CodeGenerator::writeToFile(const std::string &filename)
{
    std::ofstream file(filename);
    for (const auto &line : m_code)
    {
        file << line << std::endl;
    }
}


void CodeGenerator::addLineToSection(const std::string &line, Sections section)
{
    std::string sectionStr;

    if (section == Sections::DATA)
    {
        sectionStr = ";>--DATA SECTION--<";
    }
    else if (section == Sections::CODE)
    {
        sectionStr = ";>--CODE SECTION--<";
    }

    /*
     * put instead of section string our line string
     * and then put section string after our line string
     */

    m_codeIterator = std::find(m_code.begin(), m_code.end(), sectionStr);
    *m_codeIterator = line;
    ++m_codeIterator;

    if (m_codeIterator != m_code.end())
        m_codeIterator = m_code.insert(m_codeIterator, sectionStr);
}


void CodeGenerator::generateCode(std::unique_ptr<INode> &root)
{
    if (auto child = dynamic_cast<StatementNode *>(root.get()))
    {
        for (auto &node: child->nodes)
        {
            generateCodeNode(node);
        }
    }

    if (auto child = dynamic_cast<ForNode*>(root.get()))
    {
        for (auto &node: child->nodes)
        {
            generateCodeNode(node);
        }
    }
}


void CodeGenerator::generateCodeNode(std::unique_ptr<INode> &node)
{
    if (node == nullptr)
    {
        return;
    }

    if (auto pBinOperationNode = dynamic_cast<BinOperationNode*>(node.get()))
    {
        std::string opStr;
        if (pBinOperationNode->op.type.name == TokenTypes::ASSIGNMENT)
        {
            auto variable = (VariableNode*)(pBinOperationNode->leftOperand.get());

            generateCodeNode(pBinOperationNode->rightOperand);

            addLineToSection("pop eax", Sections::CODE);
            addLineToSection("mov " + variable->variable.value + ", eax", Sections::CODE);

            return;
        }
        else if (pBinOperationNode->op.type.name == TokenTypes::PLUS)
        {
            opStr = "add";
        }
        else if (pBinOperationNode->op.type.name == TokenTypes::MULTIPLY)
        {
            opStr = "imul";
        }
        else if (pBinOperationNode->op.type.name == TokenTypes::MINUS)
        {
            // TODO: result loses -
            opStr = "sub";
        }
        else if (pBinOperationNode->op.type.name == TokenTypes::DIVIDE)
        {
            opStr = "idiv";
        }

        m_codeIterator = m_code.end();
        generateCodeNode(pBinOperationNode->leftOperand);

        m_codeIterator = m_code.end();
        generateCodeNode(pBinOperationNode->rightOperand);

        addLineToSection("pop ebx", Sections::CODE);
        addLineToSection("pop eax", Sections::CODE);
        addLineToSection(opStr + " eax, ebx", Sections::CODE);
        addLineToSection("push eax", Sections::CODE);
    }
    else if (auto pUnarOperationNode = dynamic_cast<UnarOperationNode*>(node.get()))
    {
        if (pUnarOperationNode->op.type.name == TokenTypes::INPUT)
        {
            // TODO: ask user for input
        }
        else if (pUnarOperationNode->op.type.name == TokenTypes::OUTPUT)
        {
            addLineToSection("push ", Sections::CODE);
            generateCodeNode(pUnarOperationNode->operand);
            addLineToSection("push offset fmt", Sections::CODE);
            addLineToSection("push offset buffer", Sections::CODE);
            addLineToSection("call wsprintf", Sections::CODE);
            addLineToSection("invoke StdOut, addr buffer", Sections::CODE);
            addLineToSection("", Sections::CODE);
        }
    }
    else if (auto pProgramNameNode = dynamic_cast<ProgramNameNode*>(node.get()))
    {
        // TODO: use program name ?
    }
    else if (auto pNumberNode = dynamic_cast<NumberNode*>(node.get()))
    {
        if (m_codeIterator == m_code.end())
            addLineToSection("push " + pNumberNode->number.value, Sections::CODE);
        else
            addTextToLastLine(pNumberNode->number.value);
    }
    else if (auto pVariableNode = dynamic_cast<VariableNode*>(node.get()))
    {
        if (m_codeIterator == m_code.end())
            addLineToSection("push " + pVariableNode->variable.value, Sections::CODE);
        else
            addTextToLastLine(pVariableNode->variable.value);
    }
    else if (auto pInitVariableNode = dynamic_cast<InitVariableNode*>(node.get()))
    {
        /*
         * [variable_name] dd [value]
         */
        addLineToSection(pInitVariableNode->token.value, Sections::DATA);
        addTextToLastLine(" dd ");
        generateCodeNode(pInitVariableNode->value);
    }
    else if (auto pForNode = dynamic_cast<ForNode*>(node.get()))
    {
        static unsigned forCounter = 0;
        forCounter++;

        /*
            loop_1_st:
            mov eax, VaarrA
            cmp eax, VaarrB
            je loop_1_nd

            push VaarrA
            push offset fmt
            push offset buffer
            call wsprintf
            invoke StdOut, addr buffer

            dec VaarrA
            jmp loop_1_st

        loop_1_nd:
            // end of loop
         */

        const std::string stVarName = ((VariableNode*)pForNode->stValue.get())->variable.value;

        addLineToSection("loop_" + std::to_string(forCounter) + "_st:", Sections::CODE);
        addLineToSection("mov eax, " + stVarName, Sections::CODE);
        addLineToSection("cmp eax, ", Sections::CODE);
        generateCodeNode(pForNode->ndValue);
        addLineToSection("je loop_" + std::to_string(forCounter) + "_nd", Sections::CODE);

        // code of the loop
        generateCode(node);

        addLineToSection("dec " + stVarName, Sections::CODE);
        addLineToSection("jmp loop_" + std::to_string(forCounter) + "_st", Sections::CODE);
        addLineToSection("loop_" + std::to_string(forCounter) + "_nd:", Sections::CODE);
    }

}


void CodeGenerator::addTextToLastLine(const std::string &text)
{
    *(m_codeIterator-1) += text;
}
