#ifndef EX3_CLIENT_H
#define EX3_CLIENT_H

#include <string>
#include "SocketWriteRead.h"

using namespace std;

class Client {
    int m_socket,m_port;
    string m_ip;
    SocketWriteRead m_socketWriteRead;
public:
    Client(string ip, int port);
    void connectClient();
    void clientWrite(string data);
    void clientWrite(char c);
    string clientRead(char delimiter);
    string clientRead(unsigned long length);
    int getSocket();
    void clientClose();
};

#endif //EX3_CLIENT_H
