#include <iostream>

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


    server.Get("/", [](HttpRequest& request, HttpResponse& response) {
        
    });

    server.Run();

    std::cout << "done" << std::endl;
    return 0;
}
