#include "Server.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "Utils.h"

Server::Server(int port)
{
    m_Port = port;
    m_Sock = socket(AF_INET, SOCK_STREAM, 0);
    if (m_Sock == -1) {
        std::cout << "create socket error" << std::endl;
        return;
    }

    int yes = 1;
    if (setsockopt(m_Sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        std::cout << "setsockopt error" << std::endl;
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

    if (listen(m_Sock, 1024) < 0) {
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

        bool foundPath = false;
        if (request.GetMethod() == HttpMethod::GET && !foundPath) {
            if (m_GetMappers.find(request.GetPath()) != m_GetMappers.end()) {
                m_GetMappers[request.GetPath()](request, response);
                foundPath = true;
            }
        } 
        else if (request.GetMethod() == HttpMethod::POST && !foundPath) {
            if (m_PostMappers.find(request.GetPath()) != m_PostMappers.end()) {
                m_PostMappers[request.GetPath()](request, response);
                foundPath = true;
            }
        }
        
        if (!foundPath){
            // not found
            response.status = HttpStatus::NotFound;
            ReadHtml("./template/notfound.html", response.body);
        }

        int error = write(new_socket, response.GetData().c_str(), response.GetData().size());
        if (error < 0) {
            std::cout << "send error" << std::endl;
        }
        
        close(new_socket);
    }
}

void Server::Get(std::string&& path, MapFunction function)
{
    if (m_GetMappers.find(path) != m_GetMappers.end()) {
        std::cout << "already have [GET]" + path << std::endl;
        return;
    }
    
    // get rid of query
    int qPos = path.find("?");
    if (qPos != std::string::npos)
        path = path.substr(0, qPos);
    m_GetMappers[path] = function;
}

void Server::Post(std::string&& path, MapFunction function)
{
    if (m_PostMappers.find(path) != m_PostMappers.end()) {
        std::cout << "already have [POST]" + path << std::endl;
        return;
    }

    // get rid off query
    int qPos = path.find("?");
    if (qPos != std::string::npos)
        path = path.substr(0, qPos);
    m_PostMappers[path] = function;
}