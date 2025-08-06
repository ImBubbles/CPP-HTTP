//
// Created by bubbles on 8/5/25.
//

#pragma once

#include "HTTPRequest.h"

METHOD HTTPRequest::methodFromString(const std::string &str) {
    if (str == "GET") {
        return GET;
    }
    else if (str == "POST") {
        return POST;
    }
    else if (str == "PUT") {
        return PUT;
    }
    else if (str == "DELETE") {
        return DELETE;
    }
    return GET;
}

std::string HTTPRequest::stringFromMethod(const METHOD& method) {
    switch (method) {
        case GET:
            return "GET";
        case POST:
            return "POST";
        case PUT:
            return "PUT";
        case DELETE:
            return "DELETE";
        default:
            return "GET";
    }
}


std::string trim(const std::string& str) {
    const std::string whitespace = " \t\n\r";
    const size_t start = str.find_first_not_of(whitespace);
    if (std::string::npos == start) {
        return "";
    }
    const size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

HTTPRequest HTTPRequest::parseString(int clientSocket, std::string &rawRequest) {
    std::istringstream iss(rawRequest);
    std::string line;

    std::string methodStr;
    std::string target;
    std::string httpVersion;

    // REQUEST LINE
    if (std::getline(iss, line)) {
        std::istringstream line_stream(trim(line));
        line_stream >> methodStr >> target >> httpVersion;
    }

    std::map<std::string, std::string> headers;

    // HEADERS
    while (std::getline(iss, line) && trim(line) != "") {
        size_t pos = line.find(":");
        if (pos == std::string::npos) {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            headers[trim(key)] = trim(value);
        }
    }

    // BODY
    std::string body;
    while (std::getline(iss, line)) {
        body += line;
        if (!iss.eof()) {
            body += "\n";
        }
    }

    HTTPRequest request(clientSocket, methodFromString(methodStr), target, httpVersion, headers, body);
    return request;

}
