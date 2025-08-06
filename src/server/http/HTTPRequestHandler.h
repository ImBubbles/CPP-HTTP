//
// Created by bubbles on 8/5/25.
//

#pragma once

#include <string>
#include <sstream>
#include <thread>
#include <sys/socket.h>
#include "../../logger/Log.h"
#include "HTTPRequest.h"
#include "HTTP.h"
#include "../ServerConfig.h"

class HTTPRequestHandler {

    int clientSocket;
    std::thread* readThread;

private:
    void readRequest() const;
    void handleRequest(HTTPRequest& httpRequest) const;

public:
    ~HTTPRequestHandler();
    explicit HTTPRequestHandler(const int& clientSocket);
};
