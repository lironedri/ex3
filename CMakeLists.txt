cmake_minimum_required(VERSION 3.12)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 main.cpp Interpreter.cpp Interpreter.h Expression.h BinaryExpression.cpp BinaryExpression.h Command.h OpenServerCommand.cpp OpenServerCommand.h Plus.cpp Plus.h Minus.cpp Minus.h Mult.cpp Mult.h Div.cpp Div.h ShuntingYard.cpp ShuntingYard.h)