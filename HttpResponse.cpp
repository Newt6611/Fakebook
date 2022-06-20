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

void HttpResponse::AddHeader(std::string& key, std::string& value)
{
    m_Headers[key] = value;
}

void HttpResponse::AddCookie(std::string& key, std::string& value) 
{
    m_Cookies.emplace_back(key + "=" + value);
}

void HttpResponse::AddCookie(std::string&& key, std::string&& value) 
{
    m_Cookies.emplace_back(key + "=" + value);
}

std::string& HttpResponse::GetData()
{
    if (m_ReturnData.empty()) {
        std::cout << "response data empty... forget to call CalcData() before GetData()?\n";
    }

    return m_ReturnData;
}

void HttpResponse::CalcData()
{
    m_ReturnData = "HTTP/1.1 ";
    m_ReturnData += GetStatusString(status) + " \r\n";

    // headers
    for (std::unordered_map<std::string, std::string>::iterator it = m_Headers.begin();
            it != m_Headers.end(); ++it)
    {
        m_ReturnData += it->first + ": " + it->second + "\r\n";
    }

    // cookies
    if (m_Cookies.size() > 0) {
        std::string cookie = "";
        for (int i = 0; i < m_Cookies.size(); ++i) {
            m_ReturnData += "Set-Cookie: " + m_Cookies[i] + ";\r\n"; 
        }
    }

    m_ReturnData += "\r\n";
    m_ReturnData += body;
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