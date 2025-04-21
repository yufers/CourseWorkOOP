#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include <map>
#include <memory>

#include "../models/Books.h"
#include "../models/BookTypes.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

class BooksViewController : public HttpSimpleController<BooksViewController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/books");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        auto clientPtr = drogon::app().getDbClient();

        Mapper<Books> mpBooks(clientPtr);
        auto books = mpBooks.orderBy(Books::Cols::_book_num).offset(0).findAll();

        Mapper<BookTypes> mpBookTypes(clientPtr);
        auto bookTypes = mpBookTypes.orderBy(BookTypes::Cols::_type_id).offset(0).findAll();

        std::map<int32_t, std::string> bookTypesMap;
        for (const auto &bookType : bookTypes)
        {
            if (bookType.getTypeId())
            {
                bookTypesMap[*bookType.getTypeId()] = *bookType.getTypeName();
            }
        }

        HttpViewData data;
        data["title"] = "Список книг";
        data["books"] = books;
        data["bookTypesMap"] = bookTypesMap;
        auto resp = HttpResponse::newHttpViewResponse("ListBooks", data);
        callback(resp);
    }
};