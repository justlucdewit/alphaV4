cmake_minimum_required(VERSION 3.15)
project(alphaV4 C)

set(CMAKE_C_STANDARD 99)

add_executable(alphaV4 main.c headers/fileReader/fileReader.c headers/lexer/lexer.c)