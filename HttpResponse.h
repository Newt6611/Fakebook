#pragma once
#include <string>
#include "Utils.h"

class HttpResponse
{
public:
    HttpResponse();
    ~HttpResponse();

    std::string& GetData();

private:
    std::string GetStatusString(HttpStatus status);

public:
    HttpStatus status;
    std::string body;
    std::string returnData;
};