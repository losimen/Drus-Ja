cmake_minimum_required(VERSION 3.21)
project(Drus_Ja)

set(CMAKE_CXX_STANDARD 14)

add_executable(Drus_Ja main.cpp TokenType.cpp TokenTypeList.cpp LexicalAnalyzer.cpp SyntaxAnalyzer.cpp Token.cpp AST/ASTFactory.cpp SemanticAnalyzer.cpp SemanticAnalyzer.h)
