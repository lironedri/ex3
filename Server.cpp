#include "Server.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>

void Server::serverListen() {
    struct sockaddr_in serv_addr;

    /* First call to socket() function */
    this->m_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (this->m_socket < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    /* Initialize socket structure */
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(this->m_port);

    /* Now bind the host address using bind() call.*/
    if (bind(this->m_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    /* Now start listening for the clients, here process will
       * go in sleep mode and will wait for the incoming connection
    */

    listen(this->m_socket, 5);
}

Server::Server(int port) {
    this->m_port = port;
    this->m_socket = -1;
}

int Server::serverAccept() {
    int clilen, clientSocket;
    struct sockaddr_in cli_addr;

    clilen = sizeof(cli_addr);

    /* Accept actual connection from the client */
    clientSocket = accept(this->m_socket, (struct sockaddr *) &cli_addr, (socklen_t *) &clilen);

    if (clientSocket < 0) {
        perror("ERROR on accept");
        exit(1);
    }

    this->m_clientSocketsVector.push_back(clientSocket);
    return clientSocket;
}

void Server::serverClose() {
    for (auto &it: this->m_clientSocketsVector) {
        close(it);
    }

    close(this->m_socket);
}