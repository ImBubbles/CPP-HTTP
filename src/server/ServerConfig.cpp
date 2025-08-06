//
// Created by bubbles on 8/5/25.
//


#include "ServerConfig.h"

ServerConfig* ServerConfig::instance = nullptr;

ServerConfig *ServerConfig::getServerConfigInstance() {
    if (instance != nullptr)
        return instance;
    if (!isEnvironmentSetup)
        setupFileEnvironment();
    return loadServerConfig();
}
