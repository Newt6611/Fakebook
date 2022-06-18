#include "Server.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

Server::Server(int port)
{
    m_Port = port;
    m_Sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_Sock == -1) {
        std::cout << "create socket error" << std::endl;
        return;
    }

    bzero(&m_SockInfo, sizeof(sockaddr_in));
    m_SockInfo.sin_family = AF_INET;
    m_SockInfo.sin_addr.s_addr = INADDR_ANY;
    m_SockInfo.sin_port = htons(port);

    if (bind(m_Sock, (sockaddr*)&m_SockInfo, sizeof(sockaddr_in)) < 0) {
        std::cout << "bind socket error" << std::endl;
        return;
    }

    if (listen(m_Sock, 10) < 0) {
        std::cout << "listen error" << std::endl;
        return;
    }
}

Server::~Server()
{
    close(m_Sock);
}

void Server::Run()
{
    int new_socket;

    while (true) {
        socklen_t sock_len = sizeof(sockaddr_in);
        sockaddr_in i;
        new_socket = accept(m_Sock, (sockaddr*)&i, (socklen_t*)&sock_len);
        if (new_socket == -1) {
            std::cout << "failed accept" << std::endl;
            break;
        }
        
        char buffer[1024];
        int r = read(new_socket, buffer, 1024);
        if (r < 0) {
            std::cout << "read error" << std::endl;
        }

        // std::cout << "================================\n";
        // std::cout << buffer << std::endl;
        // std::cout << "================================\n";


        HttpRequest request(this, buffer);
        HttpResponse response;

        if (request.GetMethod() == HttpMethod::GET) {
            m_GetMappers[request.GetPath()](request, response);
        }

        int error = write(new_socket, response.GetData().c_str(), response.GetData().size());
        if (error < 0) {
            std::cout << "send error" << std::endl;
        }
        
        close(new_socket);
        break;
    }
}

void Server::Get(std::string&& path, MapFunction function)
{
    if (m_GetMappers.find(path) != m_GetMappers.end()) {
        std::cout << "already have [GET]" + path;
        return;
    }

    m_GetMappers[path] = function;
}

void Server::Post(std::string&& path, MapFunction function)
{
    if (m_PostMappers.find(path) != m_PostMappers.end()) {
        std::cout << "already have [POST]" + path;
        return;
    }

    m_PostMappers[path] = function;
}