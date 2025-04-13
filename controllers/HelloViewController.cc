#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>

#include <drogon/orm/Mapper.h>

#include "../models/Books.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

// HttpSimpleController does not allow registration of multiple handlers.
// Instead, it has one handler - asyncHandleHttpRequest. The
// HttpSimpleController is a lightweight class designed to handle really simple
// cases.
class HelloViewController : public HttpSimpleController<HelloViewController>
{
public:
    PATH_LIST_BEGIN
    // Also unlike HttpContoller, HttpSimpleController does not automatically
    // prepend the namespace and class name to the path. Thus the path of this
    // controller is at "/view".
    PATH_ADD("/view");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        std::cout << "Test 213232" << std::endl;

        auto clientPtr = drogon::app().getDbClient();
        std::cout << clientPtr << " clientPtr!" << std::endl;

        Mapper<Books> mp(clientPtr);

        auto iii = mp.count();

        std::cout << iii << " rows 111111111111111!" << std::endl;

        auto uu = mp.orderBy(Books::Cols::_book_num).limit(5).offset(0).findAll();
        std::cout << uu.size() << " rows 2222222222222222!" << std::endl;

        HttpViewData data;
        data["name"] = req->getParameter("name");
        auto resp = HttpResponse::newHttpViewResponse("HelloView", data);
        callback(resp);
    }
};