cmake_minimum_required(VERSION 3.21)
project(Drus_Ja)

set(CMAKE_CXX_STANDARD 14)

add_executable(Drus_Ja main.cpp Token.h TokenType.h TokenType.cpp TokenTypeList.cpp TokenTypeList.h LexicalAnalyzer.cpp LexicalAnalyzer.h)
