#ifndef TUE_CONFIG_DATA_POINTER_H_
#define TUE_CONFIG_DATA_POINTER_H_

#include <boost/shared_ptr.hpp>

namespace tue
{

namespace config
{

typedef unsigned int NodeIdx;

class Data;
class DataConstPointer;

class DataPointer
{
public:
    DataPointer() : idx(0) {}
    DataPointer(const boost::shared_ptr<Data>& data_, NodeIdx idx_) : data(data_), idx(idx_) {}
    bool valid() const { return data; }
    boost::shared_ptr<Data> data;
    NodeIdx idx;

    bool add(const DataConstPointer& ptr);
    void reset() { data.reset(); idx = 0; }

    friend std::ostream& operator<< (std::ostream& out, const DataPointer& d);

};

class DataConstPointer
{
public:
    DataConstPointer() : idx(0) {}
    DataConstPointer(const boost::shared_ptr<const Data>& data_, NodeIdx idx_) : data(data_), idx(idx_) {}
    DataConstPointer(const DataPointer& ptr) : data(ptr.data), idx(ptr.idx) {}
    bool valid() const { return data; }
    boost::shared_ptr<const Data> data;
    NodeIdx idx;

    void reset() { data.reset(); idx = 0; }

    friend std::ostream& operator<< (std::ostream& out, const DataConstPointer& d);
};

}

} // end namespace tue

#endif
