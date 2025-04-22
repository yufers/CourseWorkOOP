#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include <vector>

#include "../models/Books.h"
#include "../models/BookTypes.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

class BookRegisterController : public HttpSimpleController<BookRegisterController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/register_book");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {

        auto clientPtr = drogon::app().getDbClient();
        Mapper<BookTypes> mpBookTypes(clientPtr);
        auto bookTypes = mpBookTypes.orderBy(BookTypes::Cols::_type_id).offset(0).findAll();

        HttpViewData data;
        data["title"] = "Регистрация книги";
        data["bookTypes"] = bookTypes;
        auto resp = HttpResponse::newHttpViewResponse("RegisterBook", data);
        callback(resp);
    }
};