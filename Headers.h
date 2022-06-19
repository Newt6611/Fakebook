#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

#include "HttpResponse.h"
#include "HttpRequest.h"
#include "Server.h"
#include "Utils.h"

// serivces
#include "Services/UserService.h"

// thirdparties
#include "vendor/json.hpp"
using json::JSON;

#include <sqlite3.h>