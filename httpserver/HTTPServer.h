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
#include "HTTPServerConfig.h"
#include "http/HTTPRequestHandler.h"
#include "../logger/Log.h"

class HTTPServer {

    // PV MEMBER VARIABLES

private:
    int port, serverFD;
    sockaddr_in* sockAddr;
    std::thread* handlingThread;
    HTTPServerConfig* srvConfig;

    // PV MEMBER FNs

private:

    void handle();

    sockaddr* rawSockAddr() {
        return reinterpret_cast<struct sockaddr *>(sockAddr);
    }

    // PUBLIC MEMBER FNs

public:
    explicit HTTPServer();
    ~HTTPServer();
};
