#include <iostream>

#include "crow.h"

int main(int, char **)
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")([]() {
        auto page = crow::mustache::load("index.html");
        crow::mustache::context ctx;

        return page.render(ctx); });
    
    CROW_ROUTE(app, "/login/<string>")([](std::string name) {
        auto page = crow::mustache::load("index.html");
        crow::mustache::context ctx({{"person", name}});

        return page.render(ctx); });
        
    app.port(18080).multithreaded().run();
}
