//
// Created by bubbles on 8/4/25.
//

#pragma once
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include "HTTPResult.h"
#include "../Environment.h"

inline auto errorResponse = "HTTP/1.1 500 Internal Server Error\r\nContent-Length: 0\r\n\r\n";

void sendHTTPResult(const int& clientSocket, const HTTPResult& httpResult);
void sendHtml(const int& clientSocket, std::string& filePath);