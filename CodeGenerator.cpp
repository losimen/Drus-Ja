// Drus_Ja by losimen 04.12.2022

#include "CodeGenerator.h"


CodeGenerator::CodeGenerator()
{
    generateHeader();
}


void CodeGenerator::generateHeader()
{
    m_code.emplace_back("; Drus_Ja by losimen 04.12.2022");
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
    m_code.emplace_back("; --DATA SECTION--");
    m_code.emplace_back("");
    m_code.emplace_back(".code");
    m_code.emplace_back("");
    m_code.emplace_back("start:");
    m_code.emplace_back("; --CODE SECTION--");
    m_code.emplace_back("call ExitProcess");
    m_code.emplace_back("");
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
