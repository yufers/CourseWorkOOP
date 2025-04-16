#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include <map>
#include <memory>

#include "../models/Books.h"
#include "../models/BookTypes.h"
#include "../models/Readers.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

// HttpSimpleController does not allow registration of multiple handlers.
// Instead, it has one handler - asyncHandleHttpRequest. The
// HttpSimpleController is a lightweight class designed to handle really simple
// cases.
class BooksReserveController : public HttpSimpleController<BooksReserveController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/book_reserve");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        std::string bookIdStr = req->getParameter("book_id");
        int bookId = std::atoi(bookIdStr.c_str());
        
        auto clientPtr = drogon::app().getDbClient();

        Mapper<Books> mpBook(clientPtr);
        auto book = mpBook.findByPrimaryKey(bookId);

        Mapper<Readers> mpReader(clientPtr);
        auto bookReaders = mpReader.orderBy(Readers::Cols::_reader_num).offset(0).findAll();

        HttpViewData data;
        data["title"] = "Резервирование книги";
        data["book"] = book;
        data["bookReaders"] = bookReaders;
        auto resp = HttpResponse::newHttpViewResponse("ReserveBook", data);
        callback(resp);
    }
};