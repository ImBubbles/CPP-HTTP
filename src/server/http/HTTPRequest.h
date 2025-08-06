//
// Created by bubbles on 8/5/25.
//

#pragma once

#include <map>
#include <string>
#include <utility>
#include <sstream>

enum METHOD { GET, POST, PUT, DELETE };

struct HTTPRequest {

    const int clientSocket;
    const METHOD method;
    const std::string target;
    const std::string httpVersion;
    const std::map<std::string, std::string> headers;
    const std::string content;

public:
    HTTPRequest(
        const int clientSocket,
        const METHOD& method,
        std::string target,
        std::string httpVersion,
        std::map<std::string, std::string> headers,
        std::string content) :
    clientSocket(clientSocket),
    method(method),
    target(std::move(target)),
    httpVersion(std::move(httpVersion)),
    headers(std::move(headers)),
    content(std::move(content))
    {}

    static HTTPRequest parseString(int clientSocket, std::string &rawRequest);
    static METHOD methodFromString(const std::string &str);
    static std::string stringFromMethod(const METHOD &method);

};
