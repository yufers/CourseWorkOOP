#include <drogon/HttpSimpleController.h>
#include <drogon/HttpResponse.h>
#include <drogon/orm/Mapper.h>

#include "../models/Readers.h"

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

class ReaderRegisterApproveController : public HttpSimpleController<ReaderRegisterApproveController>
{
public:
    PATH_LIST_BEGIN
    PATH_ADD("/reader_register_approve");
    PATH_LIST_END

    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback) override
    {
        std::string nameId = req->getParameter("name_id");
        std::string addressId = req->getParameter("address_id");
        std::string phoneId = req->getParameter("phone_id");

        Readers reader;
        reader.setReaderName(nameId);
        reader.setReaderAddress(addressId);
        reader.setReaderPhone(phoneId);

        auto clientPtr = drogon::app().getDbClient();
        Mapper<Readers> mpReader(clientPtr);
        mpReader.insert(reader);

        HttpResponsePtr resp = HttpResponse::newHttpResponse();
        resp->setBody("<script>window.location.href = \"/readers\";</script>");
        callback(resp);
    }
};