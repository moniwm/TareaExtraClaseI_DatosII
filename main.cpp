#include <iostream>
#include "ServerSocket.h"

int main() {

    ServerSocket *serverSocket = new ServerSocket();

    while(true){
        serverSocket->receiveMessage();
    }

    serverSocket->closeSocket();

    return 0;
}

