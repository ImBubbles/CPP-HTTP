//
// Created by bubbles on 8/4/25.
//

#pragma once

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <thread>
#include "Environment.h"
#include "ServerConfig.h"
#include "http/HTTPRequestHandler.h"
#include "../logger/Log.h"

class Server {

    // PV MEMBER VARIABLES

private:
    int port, serverFD;
    sockaddr_in* sockAddr;
    std::thread* handlingThread;
    ServerConfig* srvConfig;

    // PV MEMBER FNs

private:

    void handle();

    sockaddr* rawSockAddr() {
        return reinterpret_cast<struct sockaddr *>(sockAddr);
    }

    // PUBLIC MEMBER FNs

public:
    explicit Server();
    ~Server();
};
