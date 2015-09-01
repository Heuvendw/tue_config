#ifndef _DATA_WRITER_H_
#define _DATA_WRITER_H_

#include "tue/config2/data.h"
#include "tue/config2/writer.h"

namespace tue
{
namespace config2
{

class DataWriter : public Writer
{

public:

    DataWriter() : data_(new Data()), idx_(0, MAP), is_data_owner_(true)
    {
    }

    DataWriter(Data& data) : data_(&data), idx_(0, MAP), is_data_owner_(false)
    {
    }

    ~DataWriter()
    {
        if (is_data_owner_)
            delete data_;
    }

    void writeBool(const std::string& key, bool v)
    {
        data_->addInt(idx_, key, v);
    }

    void writeInt(const std::string& key, int v)
    {
        data_->addInt(idx_, key, v);
    }

    void writeFloat(const std::string& key, double v)
    {
        data_->addFloat(idx_, key, v);
    }

    void writeString(const std::string& key, const std::string& v)
    {
        data_->addString(idx_, key, v);
    }

    void writeGroup(const std::string& name)
    {
        idx_ = data_->addGroup(idx_, name);
    }

    void endGroup()
    {
        idx_ = data_->getParent(idx_);
    }

    void writeArray(const std::string& name)
    {
        idx_ = data_->addArray(idx_, name);
    }

    void endArray()
    {
        idx_ = data_->getParent(idx_);
    }

    void writeArrayItem()
    {
        idx_ = data_->addArrayItem(idx_);
    }

    void endArrayItem()
    {
        idx_ = data_->getParent(idx_);
    }

    const Data& data() { return *data_; }

private:

    Data* data_;

    DataIndex idx_;

    bool is_data_owner_;

};

} // end namespace tue

} // end namespace config2

#endif
