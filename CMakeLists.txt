cmake_minimum_required(VERSION 3.10.2)
project(ex3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

add_executable(ex3 Main.cpp Interpreter.cpp Interpreter.h Expression.h Command.h OpenServerCommand.cpp
        OpenServerCommand.h ShuntingYard.cpp ShuntingYard.h ConnectCommand.cpp ConnectCommand.h
        DefineVarCommand.cpp DefineVarCommand.h PrintCommand.cpp PrintCommand.h SleepCommand.cpp
        SleepCommand.h IfCommand.cpp IfCommand.h LoopCommand.cpp LoopCommand.h CommandExpression.cpp
        CommandExpression.h Client.cpp Client.h Server.cpp Server.h SocketWriteRead.cpp SocketWriteRead.h
        SymbolTable.cpp SymbolTable.h ConditionParser.h ConditionParser.cpp)

target_link_libraries(ex3 pthread)