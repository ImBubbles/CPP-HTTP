cmake_minimum_required(VERSION 3.31)
project(CPP-HTTP)

# JSON LIBRARY
include(FetchContent)
FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY https://github.com/nlohmann/json.git
        GIT_TAG v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

set(CMAKE_CXX_STANDARD 26)

# INPUTS
set(CONFIG_JSON ${CMAKE_SOURCE_DIR}/src/server/defaults/resources/config.json)
set(EXAMPLE_HTML ${CMAKE_SOURCE_DIR}/src/server/defaults/html/example.html)

# OUTPUTS
set(CONFIG_HEADER ${CMAKE_SOURCE_DIR}/src/server/defaults/resources/config.h)
set(EXAMPLE_HEADER ${CMAKE_SOURCE_DIR}/src/server/defaults/html/example.h)

# GENERATE CONFIG JSON
add_custom_command(
        OUTPUT ${CONFIG_HEADER}
        COMMAND xxd -i -n resource_default_config ${CONFIG_JSON} > ${CONFIG_HEADER}
        DEPENDS ${CONFIG_JSON}
)

# GENERATE EXAMPLE HTML
add_custom_command(
        OUTPUT ${EXAMPLE_HEADER}
        COMMAND xxd -i -n resource_example_html ${EXAMPLE_HTML} > ${EXAMPLE_HEADER}
        DEPENDS ${EXAMPLE_HTML}
)

# EXEC
add_executable(
        CPP-HTTP
        src/main.cpp
        src/server/Server.cpp
        src/server/Server.h
        src/logger/Log.cpp
        src/logger/Log.h
        src/logger/LogLevel.h
        src/server/http/HTTP.cpp
        src/server/http/HTTP.h
        src/server/Environment.cpp
        src/server/Environment.h
        ${CONFIG_HEADER}
        ${EXAMPLE_HEADER}
        src/server/ServerConfig.h
        src/server/http/HTTPRequestHandler.cpp
        src/server/http/HTTPRequestHandler.h
        src/server/http/HTTPRequest.cpp
        src/server/http/HTTPRequest.h
        src/server/ServerConfig.cpp
        src/server/http/HTTPResult.cpp
        src/server/http/HTTPResult.h
        src/server/http/handlers/GetHandler.h
        src/server/http/handlers/PutHandler.h
        src/server/http/handlers/DeleteHandler.h
        src/server/http/handlers/PostHandler.h
        src/server/http/handlers/Handler.h
)

# DEPENDENCIES
add_custom_target(generate_default_headers DEPENDS ${CONFIG_HEADER} ${EXAMPLE_HEADER})
add_dependencies(CPP-HTTP generate_default_headers)
target_link_libraries(CPP-HTTP PRIVATE nlohmann_json::nlohmann_json)