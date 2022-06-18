#pragma once
#include <iostream>
#include <fstream>
#include <sstream>


enum HttpMethod {
    NONE, GET, POST
};

enum HttpStatus {
    Ok = 202,
    NotFound = 404,
    MethodNotAllowed = 405
};

inline void ReadHtml(std::string&& path, std::string& returnData) {
    std::ifstream ifs(path, std::ios::in);
        if (!ifs.is_open()) {
            std::cout << "failed to open html file path: " << path << std::endl;
            return;
        }

    std::stringstream ss;
    ss << ifs.rdbuf();
    returnData = ss.str();
    ifs.close();
}