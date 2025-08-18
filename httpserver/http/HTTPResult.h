//
// Created by bubbles on 8/5/25.
//

#pragma once

#include <string>
#include <sstream>

enum TYPE {
    TEXT_HTML,
    TEXT_CSS,
    IMAGE_JPEG,
    IMAGE_PNG,
    IMAGE_GIF,
    IMAGE_X_CON,
    IMAGE_WEBP,
    APPLICATION_PDF,
    APPLICATION_OCTET_STREAM,
    TEXT_JAVASCRIPT,
    TEXT_PLAIN,
    FAVICON
};

struct HTTPResult {
private: // PREDEFINED
    const std::string httpVersion = "HTTP/1.1";
public:
    const TYPE type;
    const bool success;
    const int length;
    std::string content;

public:
    HTTPResult(
        const TYPE& type,
        const bool success,
        const int length,
        std::string& content) :
    type(type),
    success(success),
    length(length),
    content(std::move(content)) {}

    void addContent(const std::string& key, const std::string& value);

    std::string toString() const;

    static std::string typeToString(const TYPE& type);
    static TYPE extensionToType(const std::string& filePath);

};