#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include <map>
#include <memory>
#include <string>

#include "../models/Books.h"
#include "../models/BookTypes.h"
#include "../models/Readers.h"
#include "../models/BooksInUse.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

class BookReserveApproveController : public HttpSimpleController<BookReserveApproveController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/book_reserve_approve");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        std::string bookIdStr = req->getParameter("book_id");
        int bookId = std::atoi(bookIdStr.c_str());

        std::string readerIdStr = req->getParameter("reader_id");
        int readerId = std::atoi(readerIdStr.c_str());

        auto clientPtr = drogon::app().getDbClient();

        Mapper<Books> mpBook(clientPtr);
        auto book = mpBook.findByPrimaryKey(bookId);

        book.setBookCount(*book.getBookCount() - 1);
        mpBook.update(book);

        Mapper<BooksInUse> mpBooksInUse(clientPtr);
        BooksInUse booksInUse;
        booksInUse.setBookNum(bookId);
        booksInUse.setReaderNum(readerId);
        booksInUse.setIssueDate(getCurrentDate());
        booksInUse.setReturnDate(getReturnDate(15));
        booksInUse.setReturnPeriod(15);

        mpBooksInUse.insert(booksInUse);

        Mapper<Readers> mpReader(clientPtr);
        auto bookReaders = mpReader.orderBy(Readers::Cols::_reader_num).offset(0).findAll();

        HttpViewData data;
        data["title"] = "Резервирование книги";
        data["book"] = book;
        data["bookReaders"] = bookReaders;
        auto resp = HttpResponse::newHttpViewResponse("ReserveBook", data);
        callback(resp);
    }

    ::trantor::Date getCurrentDate()
    {
        time_t t;
        time(&t);
        return ::trantor::Date(t * 1000000);
    }

    ::trantor::Date getReturnDate(int returnPeriod)
    {
        time_t t;
        time(&t);

        const time_t secondsInReturnPeriod = returnPeriod * 24 * 60 * 60;
        time_t futureTime = t + secondsInReturnPeriod;

        return ::trantor::Date(futureTime * 1000000);
    }
};