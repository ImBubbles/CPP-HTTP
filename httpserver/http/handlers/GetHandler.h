//
// Created by bubbles on 8/5/25.
//

#pragma once
#include "../HTTPResult.h"
#include "../../Environment.h"
#include "../../util/UtilString.h"

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

        // EVERYTHING WITH AN EMPTY CONTENT REQUEST BELOW
        if (!request.content.empty()) {
            return;
        }

        std::string trimmed = request.target.substr(1, request.target.size()-1);
        const TYPE type = HTTPResult::extensionToType(trimmed);

        // HTML DIRECTORY BASED
        if (type==TEXT_HTML
                || type==TEXT_CSS
                || type==TEXT_JAVASCRIPT
                ) {

            std::string path = "html/" + trimmed;
            std::string binary = readFile(path);
            if (!binary.empty()) {
                const HTTPResult httpResult(type, true, binary.size(), binary);
                sendHTTPResult(request.clientSocket, httpResult);
            }
            return;
        }

        // PAGE (STILL HTML DIRECTORY BASED)
        if (trimmed.starts_with("page/")) {
            std::string path = "html/" + UtilString::removeFirst("page/",trimmed);
            path = path.ends_with(".html") ? path : path + ".html";
            std::string binary = readFile(path);
            if (!binary.empty()) {
                const HTTPResult httpResult(TEXT_HTML, true, binary.size(), binary);
                sendHTTPResult(request.clientSocket, httpResult);
            }
            return;
        }

        // IMAGES
        if (trimmed.starts_with("images/")) {
            Log::debug("Preparing image");
            std::string binary = readFile(trimmed);
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
        if (trimmed.starts_with("files/")) {
            std::string path = "files/" + trimmed;
            Log::debug("Preparing file");
            std::string binary = readFile(path);
            Log::debug("Prepared file, ready to send");
            if (!binary.empty()) {
                Log::debug("Attempting to send file");
                const HTTPResult httpResult(type, true, binary.size(), binary);
                sendHTTPResult(request.clientSocket, httpResult);
            }
            Log::debug("file sent");
            return;
        }

        // DEFAULT - RETURN TO HOME PAGE
        HTTPServerConfig serverConfig = *loadServerConfig();
        std::string path = serverConfig.defaultHtml;
        std::string binary = readFile(path);
        if (!binary.empty()) {
            const HTTPResult httpResult(TEXT_HTML, true, binary.size(), binary);
            sendHTTPResult(request.clientSocket, httpResult);
        }

    }
};
