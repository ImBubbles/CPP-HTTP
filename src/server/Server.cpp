//
// Created by bubbles on 8/4/25.
//

#include "Server.h"

void Server::handle() {
    socklen_t sockLen = sizeof(*sockAddr);
    while (true) {

        Log::debug("Waiting for connection...");

        // CONNECTION REQUEST
        int clientSocket=accept(serverFD, rawSockAddr(), &sockLen);
        Log::debug("Attempting to accept incoming client connection");
        if(clientSocket<0) {
            Log::error("Error accepting incoming client connection");
            perror("Accept failed");
            continue;
        }
        Log::debug("Accepted incoming client connection");

        // HTTP Request

        std::thread([clientSocket]() {
            HTTPRequestHandler handler(clientSocket);
        }).detach();

    }
}

Server::~Server() {
    Log::info("Closing server...");
    Log::info("Closed client socket thread");
    Log::info("Closing server socket");
    close(serverFD);
    Log::info("Server socket closed");
    Log::info("Clearing memory-unsafe objects from memory...");
    delete(sockAddr);
    delete(srvConfig);
    Log::info("Cleared memory-unsafe objects from memory");
}

Server::Server() : serverFD(socket(AF_INET, SOCK_STREAM, 0)) {

    Log::info("Loading file environment...");
    setupFileEnvironment();
    Log::info("Loaded file environment...");
    Log::info("Loading server config...");
    srvConfig = ServerConfig::getServerConfigInstance();
    if (srvConfig==nullptr) {
        Log::error("Could not load server config");
        exit(EXIT_FAILURE);
    }
    Log::info("Loaded server config");

    // SET VALUES FROM CONFIG
    this->port=srvConfig->port;

    Log::info("Starting server...");

    Log::info("Creating server socket");
    if (serverFD < 0) {
        perror("Error creating server socket");
        exit(EXIT_FAILURE);
    }

    Log::info("Server socket created");

    auto* socketAddress = new struct sockaddr_in;

    socketAddress->sin_family = AF_INET;
    socketAddress->sin_addr.s_addr = INADDR_ANY;
    socketAddress->sin_port = htons(port);

    sockAddr = socketAddress;

    Log::info("Binding to port " + std::to_string(port));
    if (bind(serverFD, rawSockAddr(), sizeof(*sockAddr)) < 0) {
        perror("Bind failed");
        Log::error("Check to see if there is already an application running on the same port!");
        exit(EXIT_FAILURE);
    }


    Log::info("Server bound to port " + std::to_string(port));

    if (listen(serverFD, 5) < 0) {
        perror("Listen failed");
        Log::error("If this failed, you got bigger problems, I never once had this fail while making this");
        exit(EXIT_FAILURE);
    }

    Log::info("Server listening on port " + std::to_string(port));

    Log::info("Server created and ready for handling connections");

    Log::info("Creating thread for handling client socket connections");

    /*handlingThread = new std::thread(&Server::handle, this)*/;
    handle();

    Log::info("Thread created and attached, server is handling incoming connections");

}
