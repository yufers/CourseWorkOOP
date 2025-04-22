#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include "../models/BooksInUseExt.h"
#include "../models/Books.h"
#include "../models/Readers.h"

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

        Mapper<BooksInUseExt> mpReserve(clientPtr);
        Mapper<Books> mpBook(clientPtr);
        Mapper<Readers> mpReader(clientPtr);

        auto reserves = mpReserve.orderBy(BooksInUseExt::Cols::_book_in_use_num).offset(0).findAll();
        for (auto &it : reserves)
        {
            auto book = mpBook.findByPrimaryKey(*it.getBookNum());
            it.setBook(book);

            auto reader = mpReader.findByPrimaryKey(*it.getReaderNum());
            it.setReader(reader);
        }

        HttpViewData data;
        data["title"] = "Список зарезервированных книг";
        data["reserve"] = reserves;
        auto resp = HttpResponse::newHttpViewResponse("ListBooksInUse", data);
        callback(resp);
    }
};