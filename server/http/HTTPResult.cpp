//
// Created by bubbles on 8/5/25.
//

#include "HTTPResult.h"

TYPE HTTPResult::extensionToType(const std::string &filePath) {
    if (!filePath.contains('.'))
        return TYPE::TEXT_PLAIN;
    const int extensionStart = filePath.find('.');
    std::string extension = filePath.substr(extensionStart);
    if (extension == ".html")
        return TYPE::TEXT_HTML;
    else if (extension == ".jpg")
        return TYPE::IMAGE_JPEG;
    else if (extension == ".png")
        return TYPE::IMAGE_PNG;
    else if (extension == ".gif")
        return TYPE::IMAGE_GIF;
    else if (extension == ".webp")
        return TYPE::IMAGE_WEBP;
    else if (extension == ".ico")
        return TYPE::FAVICON;
    else if (extension == ".js")
        return TYPE::TEXT_JAVASCRIPT;
    else if (extension == ".css")
        return TYPE::TEXT_CSS;
    else if (extension == ".pdf")
        return TYPE::APPLICATION_PDF;
    return TYPE::TEXT_PLAIN;
}


std::string HTTPResult::typeToString(const TYPE& type) {
    switch (type) {
        case TEXT_HTML:
            return "text/HTML";
        case IMAGE_JPEG:
            return "image/jpeg";
        case IMAGE_WEBP:
            return "image/webp";
        case IMAGE_PNG:
            return "image/png";
        case IMAGE_GIF:
            return "image/gif";
        case FAVICON:
            return "image/x-icon";
        case TEXT_CSS:
            return "text/css";
        case APPLICATION_PDF:
            return "application/pdf";
        case TEXT_JAVASCRIPT:
            return "text/javascript";
        default:
            return "text/plain";
    }
}


std::string HTTPResult::toString() const {

    std::stringstream result;
    const std::string successStr = success ? "200 OK" : "404 Not Found";
    result << httpVersion << " " << successStr << "\r\n";
    result << "Content-Type: " << typeToString(type) << "\r\n";
    result << "Content-Length: " << length << "\r\n";
    result << "\r\n";
    result << content;
    return result.str();

}
