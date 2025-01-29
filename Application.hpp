// application.hpp
#pragma once
#include "server.hpp"

class Application {
private:
    Server server;
    
public:
    void appStart();
};