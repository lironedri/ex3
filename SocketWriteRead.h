#ifndef EX3_SOCKETWRITEREAD_H
#define EX3_SOCKETWRITEREAD_H

#include <string>
using namespace std;

class SocketWriteRead {
public:
    void socketWrite(int socket, string data);
    void socketWrite(int socket, char c);
    string socketRead(int socket, char delimiter);
    string socketRead(int socket, unsigned long length);
};

#endif //EX3_SOCKETWRITEREAD_H
