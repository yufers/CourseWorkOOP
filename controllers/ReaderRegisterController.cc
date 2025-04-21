#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include <vector>

#include "../models/Readers.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

class ReaderRegisterController : public HttpSimpleController<ReaderRegisterController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/register_reader");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        HttpViewData data;
        data["title"] = "Регистрация пользователя";
        auto resp = HttpResponse::newHttpViewResponse("RegisterReader", data);
        callback(resp);
    }
};