/**
 * @brief This file contains the code referring to the implementation of a client using sockets
 *
 * @author Monica Waterhouse Montoya
 * @version 1.0
 * @since 09/20/2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <iostream>

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

class ClientSocket{

public:
    int socketfd; /// File descriptor.
    int portNumber; /// The port number in which the server is listening.
    int n; /// It contains the number of characters read or written.

    struct sockaddr_in serverAddress; /// Contains the address of the server ti which we want to connect.
    struct hostent *server;

    char buffer[256];

    ClientSocket(){

        portNumber = 7000;
        socketfd = socket(AF_INET, SOCK_STREAM, 0); /// socket() creates a new socket.

        if (socketfd < 0){
            error("ERROR opening socket");
        }

        server = gethostbyname("localhost");

        if (server == NULL) {
            std::cout << stderr << "ERROR, no such host\n";
            exit(0);
        }

        bzero((char *) &serverAddress, sizeof(serverAddress)); /// Sets all values from a buffer to 0.
        serverAddress.sin_family = AF_INET;
        bcopy((char *)server->h_addr, (char *)&serverAddress.sin_addr.s_addr, server->h_length);
        serverAddress.sin_port = htons(portNumber); ///htons(portNumber) converts a host number in host byte order to a port number in network byte order.

        /**
         * connect() us called by the client to establish a connection to the server.
         */
        if (connect(socketfd,(struct sockaddr *) &serverAddress,sizeof(serverAddress)) < 0) {
            error("ERROR connecting!");
        }

    }

    void sendMessage(){

        std::cout << "Please enter the message: ";

        bzero(buffer,256);
        fgets(buffer,255,stdin);
        n = write(socketfd,buffer,strlen(buffer));

        if (n < 0){
            error("ERROR writing to socket");
        }

        bzero(buffer,256);
        n = read(socketfd,buffer,255);

        if (n < 0){
            error("ERROR reading from socket");
        }

    }

    void closeSocket(){
        close(socketfd);
    }

};

int main()
{

    ClientSocket *clientSocket = new ClientSocket();
    clientSocket->sendMessage();
    clientSocket->closeSocket();

    return 0;
}