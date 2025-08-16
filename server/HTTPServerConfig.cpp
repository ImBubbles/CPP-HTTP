//
// Created by bubbles on 8/5/25.
//


#include "HTTPServerConfig.h"

HTTPServerConfig* HTTPServerConfig::instance = nullptr;

HTTPServerConfig *HTTPServerConfig::getServerConfigInstance() {
    if (instance != nullptr)
        return instance;
    if (!isEnvironmentSetup)
        setupFileEnvironment();
    return loadServerConfig();
}
