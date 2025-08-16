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

# SHOULD BUILD HEADERS
option(CPP_HTTP_BUILD_HEADERS "Build headers from template files" OFF)

if(CPP_HTTP_BUILD_HEADERS)
    # INPUTS
    set(CONFIG_JSON ${CMAKE_SOURCE_DIR}/httpserver/defaults/resources/config.json)
    set(EXAMPLE_HTML ${CMAKE_SOURCE_DIR}/httpserver/defaults/html/example.html)

    # OUTPUTS
    set(CONFIG_HEADER httpserver/defaults/resources/config.h)
    set(EXAMPLE_HEADER httpserver/defaults/html/example.h)

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
endif()

add_custom_target(generate_default_headers DEPENDS ${CONFIG_HEADER} ${EXAMPLE_HEADER})

# EXEC
add_library(
        CPP-HTTP-LIB
        httpserver/HTTPServer.cpp
        httpserver/HTTPServer.h
        logger/Log.cpp
        logger/Log.h
        logger/LogLevel.h
        httpserver/http/HTTP.cpp
        httpserver/http/HTTP.h
        httpserver/Environment.cpp
        httpserver/Environment.h
        ${CONFIG_HEADER}
        ${EXAMPLE_HEADER}
        httpserver/HTTPServerConfig.h
        httpserver/http/HTTPRequestHandler.cpp
        httpserver/http/HTTPRequestHandler.h
        httpserver/http/HTTPRequest.cpp
        httpserver/http/HTTPRequest.h
        httpserver/HTTPServerConfig.cpp
        httpserver/http/HTTPResult.cpp
        httpserver/http/HTTPResult.h
        httpserver/http/handlers/GetHandler.h
        httpserver/http/handlers/PutHandler.h
        httpserver/http/handlers/DeleteHandler.h
        httpserver/http/handlers/PostHandler.h
        httpserver/http/handlers/Handler.h
        httpserver/util/UtilString.h
        httpserver/util/UtilString.cpp
)

# LINK THE LIBRARY TO ITS DEPENDENCIES
target_link_libraries(CPP-HTTP-LIB PUBLIC nlohmann_json::nlohmann_json)
target_include_directories(CPP-HTTP-LIB
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

# Make sure the library is built after its custom headers are generated
if(CPP_HTTP_BUILD_HEADERS)
    add_dependencies(CPP-HTTP-LIB generate_default_headers)
endif()

add_executable(
        CPP-HTTP
        main.cpp
)

# LINK THE EXECUTABLE TO THE LIBRARY
target_link_libraries(CPP-HTTP PRIVATE CPP-HTTP-LIB)