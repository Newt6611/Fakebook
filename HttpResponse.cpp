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
    returnData = "HTTP/1.0 200 ";
    returnData += GetStatusString(status);
    returnData += "\r\n\r\n";
    returnData += body;

    return returnData;
}

std::string HttpResponse::GetStatusString(HttpStatus status)
{
    switch (status)
    {
    case HttpStatus::Ok:
        return "Ok";
    case HttpStatus::NotFound:
        return "NotFound";
    case HttpStatus::MethodNotAllowed:
        return "Method Not Allowed";
    }

    return "";
}