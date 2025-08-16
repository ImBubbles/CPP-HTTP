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
#include "../HTTPServerConfig.h"

class HTTPRequestHandler {

    int clientSocket;

private:
    void handleRequest(HTTPRequest& httpRequest) const;

public:
    void readRequest() const;
    explicit HTTPRequestHandler(const int& clientSocket);
};
