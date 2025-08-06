//
// Created by bubbles on 8/4/25.
//

#include "HTTP.h"

void sendHTTPResult(const int& clientSocket, const HTTPResult& httpResult) {
    std::string asString = httpResult.toString();
    send(clientSocket, asString.c_str(), asString.size(), 0);
}

void sendHtml(const int &clientSocket, std::string &filePath) {
    std::string htmlContent = readFile(filePath);
    std::string response;

    const HTTPResult httpResult(HTML, true, htmlContent.size(), htmlContent);

    sendHTTPResult(clientSocket, httpResult);

    Log::debug("Responded with HTML: " + filePath);

}
