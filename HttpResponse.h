#pragma once
#include <string>
#include <unordered_map>
#include "Utils.h"

class HttpResponse
{
public:
    HttpResponse();
    ~HttpResponse();

    std::string& GetData();
    inline std::unordered_map<std::string, std::string>& GetHeaders() { return m_Headers; }
    
    void AddHeader(std::string&&, std::string&&);
    
private:
    std::string GetStatusString(HttpStatus status);

public:
    HttpStatus status;
    std::string body;
    std::string returnData;
    std::unordered_map<std::string, std::string> m_Headers;
};