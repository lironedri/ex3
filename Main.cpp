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
 //   ShuntingYard* t =  new ShuntingYard(symbolTable);

//    cout << t->evaluate("10.3 + 2* 6")->calculate() << "\n";
//    cout << t->evaluate("100 * 2 + 12") << "\n";
//    cout << t->evaluate("100 * ( 2 + 12 )") << "\n";
//    cout << t->evaluate("100 * ( 2 + 12 ) / 14");
    Interpreter* interpreter = new Interpreter();
    vector<string> data = interpreter->lexer(argv[1]);
//    cout << t->evaluate(data[1])->calculate() << endl;
    interpreter->parser(data);



//    StartServer();
// StartClient();

    pthread_exit(NULL);

}

void StartClient() {
    int clientSocket;
    SocketWriteRead socketWriteRead;
    string msg;

    Client client("10.0.2.2", 5402);
    //dekel hayafa
    client.connectClient();

    client.clientWrite("set controls/flight/rudder -1\r\n");
//    client.clientWrite((char) '\0');
//    cout << client.clientRead((char) '\0') << endl;
//    client.clientClose();
}

void StartServer() {
    int clientSocket;
    SocketWriteRead socketWriteRead;
    string msg;

    Server server(5400);
    server.serverListen();
    clientSocket = server.serverAccept();

    while (true) {
        cout << socketWriteRead.socketRead(clientSocket, (char) '\n') << endl;
    }
//    cin >> msg;
//    socketWriteRead.socketWrite(m_clientSocket, msg);
//    socketWriteRead.socketWrite(m_clientSocket, '\0');
//    server.serverClose();
}


