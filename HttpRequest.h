#pragma once
#include <string>
#include <sstream>
#include <unordered_map>
#include <algorithm>

#include "Utils.h"

class Server;

class HttpRequest
{
public:
    HttpRequest(Server* server, const char*);

    inline HttpMethod GetMethod() { return StringToHttpMethod(m_Method); }
    inline std::string& GetPath() { return m_Path; }
    inline std::string& GetHttpVersion() { return m_HttpVersion; }
    inline std::string& GetBody() { return m_Body; }
    inline std::unordered_map<std::string, std::string>& GetHeaders() { return m_Headers; }

private:
    void ParseRequestLine(std::string&);
    void ParseHeaderLine(std::string&);

    HttpMethod StringToHttpMethod(std::string&);

private:
    Server* server;
    std::string m_Method;
    std::string m_Path;
    std::string m_HttpVersion;
    std::string m_Body;
    std::unordered_map<std::string, std::string> m_Headers;
};