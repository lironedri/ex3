#ifndef EX3_SERVER_H
#define EX3_SERVER_H

#include <vector>

using namespace std;

class Server {
    int m_port;
    int m_socket;
    vector<int> m_clientSocketsVector;
public:
    Server(int port);
    void serverListen();
    int serverAccept();
    void serverClose();
};

#endif //EX3_SERVER_H