#pragma once
#include <iostream>
#include <string>
#include <sqlite3.h>

struct User
{
    const char* name;
    const char* account;
    const char* password;
};


class UserService
{
public:
    UserService();
    ~UserService();

    /*
     * Add New Account
     * return status 0 -> ok, -1 -> account exists, -2 -> unknow error
    **/
    int NewAccount(sqlite3* DB, std::string& name, std::string& account, std::string& password);

private:
};