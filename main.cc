#include <trantor/utils/Logger.h>
#ifdef _WIN32
#include <ws2tcpip.h>
#else
#include <netinet/tcp.h>
#include <sys/socket.h>
#endif

#include <drogon/drogon.h>

using namespace drogon;

int main()
{
    std::cout << std::filesystem::current_path() << std::endl;

    // Set HTTP listener address and port
    drogon::app()
        .addListener("0.0.0.0", 8080);

    // Load config file
    drogon::app()
        .loadConfigFile("./config.json");

    drogon::app().run();
    return 0;
}
