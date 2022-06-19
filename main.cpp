#include "Headers.h"

#include <sqlite3.h>

int main() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("test.db", &db);

    if( rc){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(0);
    }else{
        fprintf(stderr, "Opened database successfully\n");
    }


    const char sqlCommand[] = "CREATE TABLE WORDS("  
      "ID INT PRIMARY        KEY      NOT NULL," 
      "Name                  TEXT     NOT NULL," 
      "Password              TEXT     NOT NULL," 
      "Score                 INT      NOT NULL);";

    rc = sqlite3_exec(db, sqlCommand, NULL, NULL, NULL);
    if (rc) {
        std::cout << "failed to create table" << std::endl;
    }else {
        std::cout << "success" << std::endl;
    }
    sqlite3_close(db);



    // Server server(8081);

    // server.Get("/", [](HttpRequest& request, HttpResponse& response) {
    //     ReadHtml("./template/index.html", response.body);
    // });

    // server.Get("/test", [](HttpRequest& request, HttpResponse& response) {
    //     response.body = "<h1>Wow It's Works</h1>"
    //     "<h1 style=\"color:red\">Red Color</h1>"
    //     "<h1 style=\"color:blue\">Blue Color</h1>"
    //     "<h1 style=\"color:black\">Blue Color</h1>";
    // });

    // server.Post("/p", [](HttpRequest& request, HttpResponse& response) {
    //     JSON obj = JSON::Load(request.GetBody());
    //     std::cout << obj["name"] << std::endl;
    //     std::cout << obj["password"] << std::endl;
        
    //     response.AddHeader("x-token", "asdasdasdasdasd");

    //     if (obj["password"].ToString() != "12345") {
    //         response.status = HttpStatus::NotFound;
    //     } else {
    //         response.body = "success";
    //     }
    // });

    // server.Run();

    // std::cout << "done" << std::endl;
    return 0;
}