#include <iostream>
#include "ServerSocket.h"

/**
 * This program runs a server socket that receives data from a client in order to control a graph and the algorithms related to it.
 * @author Monica Waterhouse
 * @return
 */

int main() {

    ServerSocket *serverSocket = new ServerSocket();

    while(true){
        serverSocket->receiveMessage();
    }

    serverSocket->closeSocket();

    return 0;
}

