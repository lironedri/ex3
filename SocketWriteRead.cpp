//#include <zconf.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include "SocketWriteRead.h"

void SocketWriteRead::socketWrite(int socket, string data) {
    int n;

    if (socket < 0) {
        perror("ERROR bad socket");
        exit(1);
    }

    /* Send message to the server */
    n = write(socket, data.c_str(), data.length());

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}

void SocketWriteRead::socketWrite(int socket, char c) {
    int n;

    if (socket < 0) {
        perror("ERROR bad socket");
        exit(1);
    }

    /* Send message to the server */
    n = write(socket, &c, sizeof(c));

    if (n < 0) {
        perror("ERROR writing to socket");
        exit(1);
    }
}

string SocketWriteRead::socketRead(int socket, char delimiter) {
    int n;
    char c;
    string result;

    n = read(socket, &c, sizeof(c));
    while (c != delimiter) {
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }   else if (n == 0)    {
            exit(0);
        }

        result += c;
        n = read(socket, &c, sizeof(c));
    }

    return result;
}

string SocketWriteRead::socketRead(int socket, unsigned long length) {
    int n, i;
    char c;
    string result;

    if (socket < 0) {
        perror("ERROR bad socket");
        exit(1);
    }

    n = read(socket, &c, sizeof(c));
    for (i = 0; i < length; ++i) {
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        result += c;
        n = read(socket, &c, sizeof(c));
    }

    return result;
}