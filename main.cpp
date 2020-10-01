#include <iostream>
#include "LinkedList.h"
#include "ServerSocket.h"

int main() {

    ServerSocket *serverSocket = new ServerSocket();
    serverSocket->receiveMessage();
    serverSocket->closeSocket();

    return 0;
}

