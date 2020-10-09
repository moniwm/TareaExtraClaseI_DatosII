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

    std::string addNewVertex(std::string vertex){
        std::string data = "1"+ vertex;
        char charData[data.size()+1];
        strcpy(charData, data.c_str());
        n = write(socketfd,charData,strlen(charData));

        bzero(buffer,256);
        n = read(socketfd,buffer,255);

        std::string message(buffer);

        return message;

    }

    std::string addNewEdge(std::string edgeData){

        std::string data = "2"+ edgeData;
        char charData[data.size()+1];
        strcpy(charData, data.c_str());
        n = write(socketfd,charData,strlen(charData));

        bzero(buffer,256);
        n = read(socketfd,buffer,255);

        std::string message(buffer);

        return message;
    }

    std::string deleteVertex(std::string vertex){

        std::string data = "3"+ vertex;
        char charData[data.size()+1];
        strcpy(charData, data.c_str());
        n = write(socketfd,charData,strlen(charData));

        bzero(buffer,256);
        n = read(socketfd,buffer,255);

        std::string message(buffer);

        return message;
    }

   std::string deleteEdge(std::string edgeData){

       std::string data = "4"+ edgeData;
       char charData[data.size()+1];
       strcpy(charData, data.c_str());
       n = write(socketfd,charData,strlen(charData));

       bzero(buffer,256);
       n = read(socketfd,buffer,255);

       std::string message(buffer);

       return message;


    }

    std::string requestFloydWarshall(std::string verticesData){
        std::string data = "5"+ verticesData;
        char charData[data.size()+1];
        strcpy(charData, data.c_str());
        n = write(socketfd,charData,strlen(charData));

        bzero(buffer,256);
        n = read(socketfd,buffer,255);

        std::string message(buffer);

        return message;


    }

    std::string getVertices(){
        n = write(socketfd, "6", 2);

        bzero(buffer,256);
        n = read(socketfd,buffer,255);

        std::string message(buffer);

        n = write(socketfd, "Got your message!", 18);

        return message;

    }

    void closeSocket(){
        close(socketfd);
    }

};

