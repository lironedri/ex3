#include <string>
#include <vector>
#include "ConnectCommand.h"
#include "ShuntingYard.h"
#include "Client.h"

using namespace std;

int ConnectCommand::execute(vector<string> data, int index) {
    string ip = data[index + 1];
    int port = (int) ShuntingYard(this->m_symbolTable).evaluate(data[index + 2])->calculate();
    Client client(ip, port);
    client.connectClient();

    this->m_symbolTable->setClientSocket(client.getSocket());
    cin.ignore();
    return 3;
}