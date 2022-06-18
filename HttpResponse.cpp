#include "HttpResponse.h"
#include <string>

HttpResponse::HttpResponse()
{
    status = HttpStatus::Ok;
}

HttpResponse::~HttpResponse()
{
    
}

std::string& HttpResponse::GetData()
{
    returnData = "HTTP/1.1 ";
    returnData += GetStatusString(status) + " ";
    returnData += "\r\n\r\n";
    returnData += body;

    return returnData;
}

std::string HttpResponse::GetStatusString(HttpStatus status)
{
    switch (status)
    {
    case HttpStatus::Ok:
        return "200 Ok";
    case HttpStatus::NotFound:
        return "404 NotFound";
    case HttpStatus::MethodNotAllowed:
        return "405 Method Not Allowed";
    }

    return "";
}