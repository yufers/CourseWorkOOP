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

    // drogon::app().loadConfigFile("./config.yaml");

    app()
        .registerHandler(
            "/",
            [](const HttpRequestPtr &req,
               std::function<void(const HttpResponsePtr &)> &&callback)
            {
                bool loggedIn =
                    req->session()->getOptional<bool>("loggedIn").value_or(false);
                HttpResponsePtr resp;
                if (loggedIn == false)
                    resp = HttpResponse::newHttpViewResponse("LoginPage");
                else
                    resp = HttpResponse::newHttpViewResponse("LogoutPage");
                callback(resp);
            },
            {Get});

    app().registerHandler(
        "/test",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback)
        {
            std::cout << "Test 1" << std::endl;

            drogon::HttpViewData data;
            data.insert("title", std::string("TestView"));
            auto res = drogon::HttpResponse::newHttpViewResponse("TestView", data);
            std::cout << res << std::endl;
            callback(res);
        },
        {Get});

    app().registerHandler(
        "/logout",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback)
        {
            HttpResponsePtr resp = HttpResponse::newHttpResponse();
            req->session()->erase("loggedIn");
            resp->setBody("<script>window.location.href = \"/\";</script>");
            callback(resp);
        },
        {Post});

    app().registerHandler(
        "/login",
        [](const HttpRequestPtr &req,
           std::function<void(const HttpResponsePtr &)> &&callback)
        {
            HttpResponsePtr resp = HttpResponse::newHttpResponse();
            std::string user = req->getParameter("user");
            std::string passwd = req->getParameter("passwd");

            // NOTE: Do not use MD5 for the password hash under any
            // circumstances. We only use it because Drogon is not a
            // cryptography library, so it does not include a better hash
            // algorithm. Use Argon2 or BCrypt in a real product. username:
            // user, password: password123
            if (user == "user" && utils::getMd5("jadsjhdsajkh" + passwd) ==
                                      "5B5299CF4CEAE2D523315694B82573C9")
            {
                req->session()->insert("loggedIn", true);
                resp->setBody("<script>window.location.href = \"/\";</script>");
                callback(resp);
            }
            else
            {
                resp->setStatusCode(k401Unauthorized);
                resp->setBody("<script>window.location.href = \"/\";</script>");
                callback(resp);
            }
        },
        {Post});

    drogon::HttpAppFramework::instance()
        .registerHandler("/list_para",
                         [=](const HttpRequestPtr &req,
                             std::function<void(const HttpResponsePtr &)> &&callback)
                         {
                             auto para = req->getParameters();
                             HttpViewData data;
                             data.insert("title", "ListParameters");
                             data.insert("parameters", para);
                             auto resp = HttpResponse::newHttpViewResponse("ListParameters.csp", data);
                             callback(resp);
                         });

    // app().enableDynamicViewsLoading({"./views"}, "./views");
    //  Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}
