#include "BooksInUse.h"
#include "Books.h"
#include "Readers.h"

#include <iostream>

namespace drogon_model
{
namespace library
{
class BooksInUseExt : public BooksInUse
{
private:
    std::shared_ptr<Readers> reader;
    std::shared_ptr<Books> book;

public:
    explicit BooksInUseExt(const drogon::orm::Row &r, const ssize_t indexOffset = 0) noexcept : BooksInUse(r, indexOffset) {};

    explicit BooksInUseExt(const Json::Value &pJson) noexcept(false) : BooksInUse(pJson) {};

    BooksInUseExt(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false) : BooksInUse(pJson, pMasqueradingVector) {};

    BooksInUseExt() : BooksInUse() {};

    void setReader(Readers &_reader)
    {
        reader = std::make_shared<Readers>(_reader);
    };

    std::shared_ptr<Readers> getReader()
    {
        return reader;
    }

    void setBook(Books &_book)
    {
        book = std::make_shared<Books>(_book);
    };

    std::shared_ptr<Books> getBook()
    {
        return book;
    }

    std::shared_ptr<std::string> getIssueDateFormatted()
    {
        std::shared_ptr<::trantor::Date> issueDate = getIssueDate();
    
        return std::make_shared<std::string>(issueDate->toDbStringLocal());
    }
    
    std::shared_ptr<std::string> getReturnDateFormatted()
    {
        std::shared_ptr<::trantor::Date> returnDate = getReturnDate();
    
        return std::make_shared<std::string>(returnDate->toDbStringLocal());
    }
};
} // namespace library
} // namespace drogon_model