#include "UserService.h"

UserService::UserService()
{

}

UserService::~UserService()
{

}

int UserService::Login(sqlite3*DB, std::string& account, std::string& password) 
{
    return 0;
}

int UserService::NewAccount(sqlite3* DB, std::string& name, std::string& account, std::string& password)
{
    int status = -2;
    std::string checkAccount = "SELECT * FROM Users WHERE Account = '" + account + "';";
    sqlite3_stmt* stmt;
    int result = sqlite3_prepare_v2(DB, checkAccount.c_str(), -1, &stmt, NULL);
    if(result == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            status = -1;
        } 
        else {
            // insert new account
            std::string insertAccount = "INSERT INTO Users (Name, Account, Password) VALUES ('" + name + "', '" + account + "', '" + password + "');";
            int r = sqlite3_exec(DB, insertAccount.c_str(), NULL, NULL, NULL);
            status = 0;
        }
    }
    else {
        std::cout << "New Account Error Code: " << result << std::endl;
    }
    sqlite3_finalize(stmt);
    return status;
}




