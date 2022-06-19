#include "Headers.h"

sqlite3* DB;

void InitDatabase() {
    char *zErrMsg = 0;
    int err = sqlite3_open("Facebook-Clone.db", &DB);
    if(err) {
        std::cout << "Can't open database: " << "Facebook-Clone" << sqlite3_errmsg(DB);
        return;
    } else {
        std::cout << "success open database\n";
    }

    // Create User Table
    const char* createUserTable = "CREATE TABLE Users("  
                        "ID INTEGER PRIMARY KEY                AUTOINCREMENT," 
                        "Name                               TEXT     NOT NULL," 
                        "Account                            TEXT     NOT NULL,"
                        "Password                           TEXT     NOT NULL);"; 
    sqlite3_exec(DB, createUserTable, NULL, NULL, NULL);
}

int main() {
    Server server(8081);
    InitDatabase();

    UserService userService;

    server.Get("/", [&](HttpRequest& request, HttpResponse& response) {
        ReadHtml("./template/login.html", response.body);
    });

    server.Post("/login", [&](HttpRequest& request, HttpResponse& response) {
        JSON obj = JSON::Load(request.GetBody());
        std::cout << obj["account"].ToString() << std::endl;
        std::cout << obj["password"].ToString() << std::endl;

        response.AddHeader("Content-Type", "application/json");
        response.body = "{\"success\": true}";
        
    });

    server.Post("/register", [&](HttpRequest& request, HttpResponse& response){
        JSON obj = JSON::Load(request.GetBody());
        std::string account = obj["account"].ToString();
        std::string password = obj["password"].ToString();
        std::string name = obj["name"].ToString();
        
        int status = userService.NewAccount(DB, name, account, password);
        
        JSON returnObj;
        if (status == 0) {
            returnObj = JSON(
                {
                    "status", status,
                    "message", "success",
                    "account", account,
                    "password", password
                }
            );
        } 
        else {
            returnObj = JSON(
                {
                    "status", status,
                    "message", "account already exsits",
                    "account", account
                }
            );
        }

        response.body = returnObj.ToString();
    });


    server.Run();
    
    sqlite3_close(DB);

    std::cout << "done" << std::endl;
    return 0;
}