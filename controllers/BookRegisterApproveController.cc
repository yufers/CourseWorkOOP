#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include "../models/Books.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

class BookRegisterApproveController : public HttpSimpleController<BookRegisterApproveController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/book_register_approve");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        std::string nameId = req->getParameter("book_name_id");
        std::string authorId = req->getParameter("book_author_id");
        std::string quantityId = req->getParameter("book_quantity_id");
        std::string typeId = req->getParameter("book_type_id");

        Books book;
        book.setBookName(nameId);
        book.setBookAuthor(authorId);
        book.setBookCount(std::atoi(quantityId.c_str()));
        book.setTypeId(std::atoi(typeId.c_str()));

        auto clientPtr = drogon::app().getDbClient();
        Mapper<Books> mpBooks(clientPtr);
        mpBooks.insert(book);

        HttpResponsePtr resp = HttpResponse::newHttpResponse();
        resp->setBody("<script>window.location.href = \"/books\";</script>");
        callback(resp);
    }
};