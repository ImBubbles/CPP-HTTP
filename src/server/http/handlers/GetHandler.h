//
// Created by bubbles on 8/5/25.
//

#pragma once
#include "../HTTPResult.h"
#include "../../Environment.h"

class GetHandler final {
public:
    static void handle(const HTTPRequest &request) {

        // FAVICON
        if (request.target=="/favicon.ico") {
            std::string path = "images/favicon.ico";
            std::string binary = readFile(path);
            const HTTPResult httpResult(FAVICON, true, binary.size(), binary);
            sendHTTPResult(request.clientSocket, httpResult);
            return;
        }

        // CSS
        if (request.content.empty() && request.target.ends_with(".css")) {
            const std::string trimmed = request.target.substr(1, request.target.size()-1);
            std::string path = "html/" + trimmed;
            std::string binary = readFile(path);
            if (!binary.empty()) {
                const HTTPResult httpResult(CSS, true, binary.size(), binary);
                sendHTTPResult(request.clientSocket, httpResult);
            }
            return;
        }

        // IMAGES
        if (request.content.empty() && request.target.starts_with("/images/")) {
            const std::string trimmed = request.target.substr(sizeof("/images/")-1, request.target.size());
            std::string path = "images/" + trimmed;
            Log::debug("Preparing image");
            std::string binary = readFile(path);
            TYPE type = HTTPResult::extensionToType(path);
            Log::debug("Prepared image, ready to send");
            if (!binary.empty()) {
                Log::debug("Attempting to send image");
                const HTTPResult httpResult(type, true, binary.size(), binary);
                sendHTTPResult(request.clientSocket, httpResult);
            }
            Log::debug("Image sent");
            return;
        }

        // FILES
        if (request.content.empty() && request.target.starts_with("/files/")) {
            const std::string trimmed = request.target.substr(sizeof("/files/")-1, request.target.size());
            std::string path = "files/" + trimmed;
            Log::debug("Preparing file");
            std::string binary = readFile(path);
            TYPE type = HTTPResult::extensionToType(path);
            Log::debug("Prepared file, ready to send");
            if (!binary.empty()) {
                Log::debug("Attempting to send file");
                const HTTPResult httpResult(type, true, binary.size(), binary);
                sendHTTPResult(request.clientSocket, httpResult);
            }
            Log::debug("file sent");
            return;
        }

        // PAGE
        if (request.content.empty() && request.target.starts_with("/page/")) {
            const std::string trimmed = request.target.substr(sizeof("/page/")-1, request.target.size());
            std::string path = "html/" + trimmed + ".html";
            std::string binary = readFile(path);
            if (!binary.empty()) {
                const HTTPResult httpResult(HTML, true, binary.size(), binary);
                sendHTTPResult(request.clientSocket, httpResult);
            }
        }

    }
};
