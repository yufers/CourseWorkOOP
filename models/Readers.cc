/**
 *
 *  Readers.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Readers.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon::orm;
using namespace drogon_model::library;

const std::string Readers::primaryKeyName = "reader_num";
const bool Readers::hasPrimaryKey = true;
const std::string Readers::tableName = "\"readers\"";

const std::vector<typename Readers::MetaData> Readers::metaData_={
};
const std::string &Readers::getColumnName(size_t index) noexcept(false)
{
    assert(index < metaData_.size());
    return metaData_[index].colName_;
}
Readers::Readers(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 0 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
    }

}

Readers::Readers(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 0)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
}

Readers::Readers(const Json::Value &pJson) noexcept(false)
{
}

void Readers::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 0)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
}

void Readers::updateByJson(const Json::Value &pJson) noexcept(false)
{
}

void Readers::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Readers::insertColumns() noexcept
{
    static const std::vector<std::string> inCols={
    };
    return inCols;
}

void Readers::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
}

const std::vector<std::string> Readers::updateColumns() const
{
    std::vector<std::string> ret;
    return ret;
}

void Readers::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
}
Json::Value Readers::toJson() const
{
    Json::Value ret;
    return ret;
}

Json::Value Readers::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 0)
    {
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    return ret;
}

bool Readers::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    return true;
}
bool Readers::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                 const std::vector<std::string> &pMasqueradingVector,
                                                 std::string &err)
{
    if(pMasqueradingVector.size() != 0)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Readers::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    return true;
}
bool Readers::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                               const std::vector<std::string> &pMasqueradingVector,
                                               std::string &err)
{
    if(pMasqueradingVector.size() != 0)
    {
        err = "Bad masquerading vector";
        return false;
    }
    try {
    }
    catch(const Json::LogicError &e)
    {
      err = e.what();
      return false;
    }
    return true;
}
bool Readers::validJsonOfField(size_t index,
                               const std::string &fieldName,
                               const Json::Value &pJson,
                               std::string &err,
                               bool isForCreation)
{
    switch(index)
    {
        default:
            err="Internal error in the server";
            return false;
    }
    return true;
}
