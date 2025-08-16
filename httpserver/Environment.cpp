//
// Created by bubbles on 8/4/25.
//

#include "Environment.h"
#include <nlohmann/json.hpp>
#include "defaults/resources/config.h"
#include "defaults/html/example.h"

int ensureExistence(const std::string& filePath) {
    Log::debug("Ensuring file "+filePath);
    if (std::filesystem::exists(filePath)) {
        return 1;
    }
    std::ofstream outfile(filePath);
    if (outfile.is_open()) {
        outfile.close();
        return 0;
    }
    outfile.close();
    return -1;
}

int ensureExistence(const std::string& filePath, const std::string& defaultValue) {
    const int result = ensureExistence(filePath);
    if (result!=0) {
        return result;
    }
    std::fstream file(filePath);
    file << defaultValue;
    file.close();
    return result;
}

std::string readFile(std::string& filePath) {
    Log::debug("Reading file "+filePath);
    std::ifstream file(filePath);
    if (!file.is_open()) {
        Log::debug("Could not find file: " + filePath);
        return "";
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


void setupFileEnvironment() {

    std::filesystem::create_directories("html");
    std::filesystem::create_directories("resources");
    std::filesystem::create_directories("images");
    std::filesystem::create_directories("files");

    const std::string defaultCfg(reinterpret_cast<char*>(resource_default_config), resource_default_config_len);

    int cfgCreate = ensureExistence("./resources/config.json", defaultCfg);
    Log::debug("Config loaded with code: " + std::to_string(cfgCreate));

    isEnvironmentSetup = true;
    const HTTPServerConfig* serverCfgPtr = loadServerConfig();

    if (serverCfgPtr==nullptr) {
        Log::error("Could not load server config during environment setup");
        isEnvironmentSetup = false;
        return;
    }

    const HTTPServerConfig serverCfg = *serverCfgPtr;

    Log::LOG_FILTER = serverCfg.loggerFilter;

    const std::string defaultHtml(reinterpret_cast<char*>(resource_example_html), resource_example_html_len);

    const int exampleCreate = ensureExistence(serverCfg.defaultHtml, defaultHtml);
    Log::debug("Home html loaded with code: " + std::to_string(exampleCreate));

}

HTTPServerConfig* loadServerConfig() {
    std::ifstream configFile("./resources/config.json");
    if (!configFile.is_open()) {
        return nullptr;
    }
    nlohmann::json json = nlohmann::json::parse(configFile);
    if (json.is_null()) {
        return nullptr;
    }
    auto* result = new HTTPServerConfig{json["loggerFilter"], json["port"], json["home"]};
    return result;
}