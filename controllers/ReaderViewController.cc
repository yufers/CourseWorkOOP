#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include "../models/Readers.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

class ReaderViewController : public HttpSimpleController<ReaderViewController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/readers");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        auto clientPtr = drogon::app().getDbClient();

        Mapper<Readers> mpReaders(clientPtr);
        auto readers = mpReaders.orderBy(Readers::Cols::_reader_num).offset(0).findAll();

        HttpViewData data;
        data["title"] = "Список пользователей";
        data["readers"] = readers;
        auto resp = HttpResponse::newHttpViewResponse("ListReaders", data);
        callback(resp);
    }
};