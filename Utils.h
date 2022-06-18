#pragma once

enum HttpMethod {
    NONE, GET, POST
};

enum HttpStatus {
    Ok = 202,
    NotFound = 404,
    MethodNotAllowed = 405
};