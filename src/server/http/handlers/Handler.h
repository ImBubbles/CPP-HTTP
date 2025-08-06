//
// Created by bubbles on 8/5/25.
//

#pragma once

#include "GetHandler.h"
#include "DeleteHandler.h"
#include "PostHandler.h"
#include "PutHandler.h"
#include "../HTTPRequest.h"
#include "../HTTP.h"

class Handler {
public:
    virtual ~Handler() = delete;

    virtual void handle(HTTPRequest &request);
public:
    static void handleMethod(const HTTPRequest &request) {
        switch (request.method) {
            case METHOD::GET:
                GetHandler::handle(request);
                break;
            case METHOD::POST:
                PostHandler::handle(request);
                break;
            case METHOD::PUT:
                PutHandler::handle(request);
                break;
            case METHOD::DELETE:
                DeleteHandler::handle(request);
                break;
            default:
                break;
        }
    }
};