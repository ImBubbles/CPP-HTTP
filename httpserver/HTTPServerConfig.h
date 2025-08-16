//
// Created by bubbles on 8/4/25.
//

#pragma once

#include <string>
#include <utility>

#include "Environment.h"


struct HTTPServerConfig {
protected:
    static HTTPServerConfig* instance;
public:
    const int loggerFilter;
    const int port;
    const std::string defaultHtml;

    HTTPServerConfig(
        const int &loggerFilter,
        const int &port,
        std::string defaultHtml
        ):
    loggerFilter(loggerFilter),
    port(port),
    defaultHtml(std::move(defaultHtml)) {
        instance=this;
    }

    static HTTPServerConfig* getServerConfigInstance();

};
