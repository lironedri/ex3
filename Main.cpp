#include <iostream>
#include "Interpreter.h"
#include "ShuntingYard.h"
#include "Server.h"
#include "SocketWriteRead.h"
#include "Client.h"
#include "SymbolTable.h"

void StartServer();

void StartClient();

int main(int argc, const char *argv[]) {
//    SymbolTable* symbolTable = new SymbolTable();
//    ShuntingYard* t =  new ShuntingYard(symbolTable);
//
//    cout << t->evaluate("10.3 + 2* 6")->calculate() << "\n";
//    cout << t->evaluate("100 * 2 + 12") << "\n";
//    cout << t->evaluate("100 * ( 2 + 12 )") << "\n";
//    cout << t->evaluate("100 * ( 2 + 12 ) / 14");
//    Interpreter* interpreter = new Interpreter();
//    vector<string> data = interpreter->lexer(argv[1]);
//    cout << t->evaluate(data[1])->calculate() << endl;
//    interpreter->parser(data);



 //   StartServer();
 StartClient();

}

void StartClient() {
    int clientSocket;
    SocketWriteRead socketWriteRead;
    string msg;

    Client client("127.0.0.1", 7542);
    client.connectClient();

    client.clientWrite("Liron HaMalka");
    client.clientWrite((char) '\0');
    cout << client.clientRead((char) '\0') << endl;
    client.clientClose();
}

void StartServer() {
    int clientSocket;
    SocketWriteRead socketWriteRead;
    string msg;

    Server server(7542);
    server.serverListen();
    clientSocket = server.serverAccept();

    cout << socketWriteRead.socketRead(clientSocket, (char) '\0') << endl;
    cin >> msg;
    socketWriteRead.socketWrite(clientSocket, msg);
    socketWriteRead.socketWrite(clientSocket, '\0');
    server.serverClose();
}


