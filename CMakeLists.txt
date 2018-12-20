cmake_minimum_required(VERSION 3.12)
project(ex3)

set(CMAKE_CXX_STANDARD 14)

add_executable(ex3 Main.cpp Interpreter.cpp Interpreter.h Expression.h BinaryExpression.cpp BinaryExpression.h Command.h OpenServerCommand.cpp OpenServerCommand.h Plus.cpp Plus.h Minus.cpp Minus.h Mult.cpp Mult.h Div.cpp Div.h ShuntingYard.cpp ShuntingYard.h ConnectCommand.cpp ConnectCommand.h VarCommand.cpp VarCommand.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp SleepCommand.h IfCommand.cpp IfCommand.h LoopCommand.cpp LoopCommand.h CommandExpression.cpp CommandExpression.h)