#include "Headers.h"

int main() {
      
    Server server(8081);

    server.Get("/", [](HttpRequest& request, HttpResponse& response) {
        ReadHtml("./template/index.html", response.body);
    });

    server.Get("/test", [](HttpRequest& request, HttpResponse& response) {
        response.body = "<h1>Wow It's Works</h1>"
        "<h1 style=\"color:red\">Red Color</h1>"
        "<h1 style=\"color:blue\">Blue Color</h1>"
        "<h1 style=\"color:black\">Blue Color</h1>";
    });

    server.Post("/p", [](HttpRequest& request, HttpResponse& response) {
        JSON obj = JSON::Load(request.GetBody());
        std::cout << obj["name"] << std::endl;
        std::cout << obj["password"] << std::endl;
        
        response.AddHeader("x-token", "asdasdasdasdasd");

        if (obj["password"].ToString() != "12345") {
            response.status = HttpStatus::NotFound;
        } else {
            response.body = "success";
        }
    });

    server.Run();

    std::cout << "done" << std::endl;
    return 0;
}