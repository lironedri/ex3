#include <string>
#include <vector>
#include <unistd.h>
#include "OpenServerCommand.h"
#include "Server.h"
#include "ShuntingYard.h"
#include "SocketWriteRead.h"

using namespace std;

#define NEW_LINE '\n'
#define SECOND_IN_MICRO 1000000
#define DELIMITER ','

void parseLine(string line, SymbolTable *symbolTable) {
    size_t pos = 0;
    std::string token;
    int index = 0;
    while ((pos = line.find(DELIMITER)) != std::string::npos) {
        token = line.substr(0, pos);
        symbolTable->insertPathValue(index++, stod(token));
        line.erase(0, pos + 1);
    }
}

static void ReadFromSimulator(int simulatorSocket, int hz, SymbolTable *symbolTable) {
    SocketWriteRead socketWriteRead;
    string line;
    bool b = false;
    while (true) {
        if (b) break;
        line = socketWriteRead.socketRead(simulatorSocket, (char) NEW_LINE);
        cout << line << endl;
        parseLine(line, symbolTable);
    }
}

int OpenServerCommand::execute(vector<string> data, int index) {
    int port = (int) ShuntingYard(this->m_symbolTable).evaluate(data[index + 1])->calculate();
    int hz = (int) ShuntingYard(this->m_symbolTable).evaluate(data[index + 2])->calculate();
    int clientSocket;
    SocketWriteRead socketWriteRead;

    Server server(port);
    server.serverListen();
    clientSocket = server.serverAccept();
    // TODO
    socketWriteRead.socketRead(clientSocket, (char) NEW_LINE);
    cout << "connected" << endl;

    thread t(ReadFromSimulator, clientSocket, hz, this->m_symbolTable);
    t.detach();

    return 3;
}