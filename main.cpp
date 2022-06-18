#include <iostream>
#include "HttpResponse.h"
#include "Server.h"

// void* proccess(void* fd) {
//     int sock_fd = *(int*)fd;

//     std::cout <<sock_fd<< std::endl;
//     std::cout << "accept" << std::endl;

//     char response[] = "HTTP/1.1 200 OK\r\n\r\n <h1>My Web</h1>";
//     int error = write(sock_fd, response, strlen(response));
//     if (error == -1) {
//         std::cout << "send error" << std::endl;
//         pthread_exit(NULL);
//     }

//     std::cout << "send " << std::endl;
//     pthread_exit(NULL);
// }

int main() {
    
    Server server(8080);


    server.Get("/test", [](HttpRequest& request, HttpResponse& response) {
        response.body = "<h1>Wow It's Works</h1>"
        "<h1 style=\"color:red\">Red Color</h1>"
        "<h1 style=\"color:blue\">Blue Color</h1>"
        "<h1 style=\"color:black\">Blue Color</h1>";
    });

    server.Run();

    std::cout << "done" << std::endl;
    return 0;
}
