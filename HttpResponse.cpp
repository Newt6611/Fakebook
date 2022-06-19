#include "HttpResponse.h"
#include <string>

HttpResponse::HttpResponse()
{
    status = HttpStatus::Ok;
}

HttpResponse::~HttpResponse()
{
    
}

void HttpResponse::AddHeader(std::string&& key, std::string&& value)
{
    m_Headers[key] = value;
}

std::string& HttpResponse::GetData()
{
    returnData = "HTTP/1.1 ";
    returnData += GetStatusString(status) + " \r\n";

    for (std::unordered_map<std::string, std::string>::iterator it = m_Headers.begin();
            it != m_Headers.end(); ++it)
    {
        returnData += it->first + ": " + it->second + "\r\n";
    }

    returnData += "\r\n";
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