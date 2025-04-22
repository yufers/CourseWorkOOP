#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include "../models/BooksInUse.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

class ReserveViewController : public HttpSimpleController<ReserveViewController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/reserve");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        auto clientPtr = drogon::app().getDbClient();

        Mapper<BooksInUse> mpReserve(clientPtr);
        auto reserve = mpReserve.orderBy(BooksInUse::Cols::_book_in_use_num).offset(0).findAll();

        HttpViewData data;
        data["title"] = "Список зарезервированных книг";
        data["reserve"] = reserve;
        auto resp = HttpResponse::newHttpViewResponse("ListBooksInUse", data);
        callback(resp);
    }
};