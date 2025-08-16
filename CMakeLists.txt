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
set(CONFIG_JSON ${CMAKE_SOURCE_DIR}/server/defaults/resources/config.json)
set(EXAMPLE_HTML ${CMAKE_SOURCE_DIR}/server/defaults/html/example.html)

# OUTPUTS
set(CONFIG_HEADER ${CMAKE_SOURCE_DIR}/server/defaults/resources/config.h)
set(EXAMPLE_HEADER ${CMAKE_SOURCE_DIR}/server/defaults/html/example.h)

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
        main.cpp
        server/HTTPServer.cpp
        server/HTTPServer.h
        logger/Log.cpp
        logger/Log.h
        logger/LogLevel.h
        server/http/HTTP.cpp
        server/http/HTTP.h
        server/Environment.cpp
        server/Environment.h
        ${CONFIG_HEADER}
        ${EXAMPLE_HEADER}
        server/HTTPServerConfig.h
        server/http/HTTPRequestHandler.cpp
        server/http/HTTPRequestHandler.h
        server/http/HTTPRequest.cpp
        server/http/HTTPRequest.h
        server/HTTPServerConfig.cpp
        server/http/HTTPResult.cpp
        server/http/HTTPResult.h
        server/http/handlers/GetHandler.h
        server/http/handlers/PutHandler.h
        server/http/handlers/DeleteHandler.h
        server/http/handlers/PostHandler.h
        server/http/handlers/Handler.h
        server/util/UtilString.h
        server/util/UtilString.cpp
)

# DEPENDENCIES
add_custom_target(generate_default_headers DEPENDS ${CONFIG_HEADER} ${EXAMPLE_HEADER})
add_dependencies(CPP-HTTP generate_default_headers)
target_link_libraries(CPP-HTTP PRIVATE nlohmann_json::nlohmann_json)