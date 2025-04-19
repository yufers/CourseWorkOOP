#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

using namespace drogon;
using namespace drogon::orm;

class HomeController : public HttpSimpleController<HomeController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        HttpViewData data;
        data["title"] = "Главная страница библиотеки";
        auto resp = HttpResponse::newHttpViewResponse("HomeView", data);
        callback(resp);
    }
};