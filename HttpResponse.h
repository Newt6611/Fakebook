#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include "Utils.h"

class Server;

class HttpResponse
{
public:
    HttpResponse();
    ~HttpResponse();

    std::string& GetData();
    inline std::unordered_map<std::string, std::string>& GetHeaders() { return m_Headers; }
    
    void AddHeader(std::string&, std::string&);
    void AddHeader(std::string&&, std::string&&);

    void AddCookie(std::string&, std::string&);
    void AddCookie(std::string&&, std::string&&);
private:
    void CalcData();
    std::string GetStatusString(HttpStatus status);

public:
    HttpStatus status;
    std::string body;
    std::unordered_map<std::string, std::string> m_Headers;
    std::vector<std::string> m_Cookies;

private:
    std::string m_ReturnData;

friend class Server;
};