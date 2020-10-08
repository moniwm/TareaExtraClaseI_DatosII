/**
 * @brief This file contains the code referring to the implementation of a server using sockets
 *
 * @author Monica Waterhouse Montoya
 * @version 1.0
 * @since 09/20/2020
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include "Graph.h"

using namespace std;

/**
 * @brief This function is called when a system call fails
 * @param msg the message displayed when the error occurs
 */
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

class ServerSocket{
    Graph *graph;

public:

    int socketfd, newSocketfd; /// File descriptors.
    int portNumber; /// The port number on which the server accepts connections.
    socklen_t clientLength; /// Stores the size of the address of the client.
    int n; /// It contains the number of characters read or written.
    char buffer[256]; /// The server reads characters from the socket connection into this buffer.
    struct sockaddr_in serverAddress, clientAddress; /// Is a structure that contains an  internet address.



    ServerSocket(){

        graph = new Graph();
        portNumber = 7000;
        socketfd = socket(AF_INET, SOCK_STREAM, 0); /// socket() creates a new socket.

        if (socketfd < 0){
            error("ERROR opening socket");
        }

        bzero((char *) &serverAddress, sizeof(serverAddress)); /// Sets all values from a buffer to 0.

        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = INADDR_ANY;
        serverAddress.sin_port = htons(portNumber); ///htons(portNumber) converts a host number in host byte order to a port number in network byte order.

        /**
         * @brief bind() Tries to bind a socket to an address, in this case the address of the current host and port number
         * in which the server will run.
         */
        if (bind(socketfd, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0){
            error("ERROR on binding");
        }

        /**
         * @brief listen() allos the process to listen on the socket for connections.
         */
        listen(socketfd,5); /// 5 is the maximum size of connections that can be waiting while the process handles a connection.

        clientLength = sizeof(clientAddress);

        /**
         * @brief accept() block the process until a client connects to the server and wakes up the process once a connection
         * has been made.
         */
        newSocketfd = accept(socketfd, (struct sockaddr *) &clientAddress, &clientLength);

        if (newSocketfd < 0){
            error("Error accepting a connection.");
        }

        std::cout<<"Connection successfully made! Listening... \n";
    }

    /**
     * This method initializes de buffer using the bzero() function and then reads from the socket.
     * It also sends a message to the client saying it received its message.
     *
     */
    void receiveMessage(){
        bzero(buffer,256);
        n = read(newSocketfd,buffer,255);

        if (n < 0){
            error("Error reading from socket!");
        }

        if(buffer[0]=='1'){

            std::string vertex(1, buffer[1]);

            std::string result = graph->addVertex(vertex);

            char message[result.size()+1];
            strcpy(message, result.c_str());

            n = write(newSocketfd, message, strlen(message));

        }

        else if(buffer[0] == '2'){
            std::string startVertex(1, buffer[1]);
            std::string endVertex(1, buffer[3]);

            int cost = buffer[2] - '0';

            std::string result = graph->addEdge(startVertex, cost, endVertex);

            char message[result.size()+1];
            strcpy(message, result.c_str());

            n = write(newSocketfd, message, strlen(message));
        }

        else if(buffer[0]=='3'){
            std::cout << "Eliminemos un vértice";
        }
        else if(buffer[0]=='4'){
            std::cout << "Eliminemos un edge";
        }
        else if(buffer[0]=='5'){
            std::cout << "Floyd Warshall";
        }

        else if(buffer[0] == '6'){

            std::string vertices = graph->getAdjacencyMatrix();

            char message[vertices.size()+1];
            strcpy(message, vertices.c_str());

            n = write(newSocketfd, message, strlen(message));
            graph->printVertices();
        }

        else if (n < 0) {
            error("ERROR writing to socket");
        }


    }


    /**
     * Closes the server socket.
     */
    void closeSocket(){
        close(newSocketfd);
        close(socketfd);
        std::cout << "Socket closed! \n";
    }

};



