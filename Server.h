#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>

// sockets
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

#include <pthread.h>

#include "Utils.h"

class HttpRequest;
class HttpResponse;

using MapFunction = std::function<void(HttpRequest&, HttpResponse&)>;

class Server
{
private:

public:
    Server(int port);
    ~Server();

    void Get(std::string&& path, MapFunction);
    void Post(std::string&& path, MapFunction);
    void Run();

private:
    int m_Port;
    int m_Sock;
    sockaddr_in m_SockInfo;

    std::unordered_map<std::string, MapFunction> m_GetMappers;
    std::unordered_map<std::string, MapFunction> m_PostMappers;
};