//
// Created by bubbles on 8/5/25.
//

#include "HTTPRequestHandler.h"
#include "handlers/Handler.h"

void HTTPRequestHandler::handleRequest(HTTPRequest &httpRequest) const {

    const HTTPServerConfig* serverConfigPtr = HTTPServerConfig::getServerConfigInstance();
    if (serverConfigPtr==nullptr)
        return;
    const HTTPServerConfig serverConfig = *serverConfigPtr;

    // CHECK IF DEFAULT
    if (httpRequest.method == GET && httpRequest.target == "/") {
        std::string dfHtml = serverConfig.defaultHtml;
        sendHtml(clientSocket, dfHtml);
        close(clientSocket);
        return;
    }

    Handler::handleMethod(httpRequest);
    close(clientSocket);

}


void HTTPRequestHandler::readRequest() const {

    std::stringstream requestStream;
    char buffer[4096];

    while (true) {
        ssize_t bytesRead = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
        if (bytesRead <= 0) {
            Log::error("Connection lost while reading HTTP request");
            return;
        }
        buffer[bytesRead] = '\0';
        requestStream << buffer;

        // Check if the end of headers has been reached
        std::string request = requestStream.str();
        if (request.find("\r\n\r\n") != std::string::npos) {
            break;
        }
    }

    std::string request = requestStream.str();

    HTTPRequest httpRequest(HTTPRequest::parseString(clientSocket, request));
    handleRequest(httpRequest);

    Log::debug("HTTP Method: " + HTTPRequest::stringFromMethod(httpRequest.method));
    Log::debug("HTTP Target: " + httpRequest.target);
    Log::debug("HTTP Version: " + httpRequest.httpVersion);
    std::string printedContent = httpRequest.content.size()==0 ? "[EMPTY CONTENT]" : httpRequest.content;
    Log::debug("HTTP Content: " + httpRequest.content);

}


HTTPRequestHandler::HTTPRequestHandler(const int& clientSocket) {
    this->clientSocket = clientSocket;
    readRequest();
}