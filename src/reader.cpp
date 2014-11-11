#include "tue/config2/reader.h"
#include "tue/config2/node.h"
#include "tue/config2/configuration.h"

namespace tue
{
namespace config
{

// ----------------------------------------------------------------------------------------------------

Reader::Reader(const tue::config::Configuration& cfg) : idx_(0), cfg_(&cfg)
{
}

// ----------------------------------------------------------------------------------------------------

Reader::~Reader()
{
}

// ----------------------------------------------------------------------------------------------------

bool Reader::read(const std::string& name)
{
    Label label;
    if (cfg_->getLabel(name, label) && cfg_->nodes[idx_]->readGroup(label, idx_))
        return true;
    return false;
}

// ----------------------------------------------------------------------------------------------------

bool Reader::end()
{   
    NodeIdx parent = cfg_->nodes[idx_]->parent;
    if (parent == -1)
        return false;

    idx_ = parent;
    return true;
}

// ----------------------------------------------------------------------------------------------------

bool Reader::next()
{
    if (cfg_->nodes[idx_]->type() == ARRAY)
        return cfg_->nodes[idx_]->firstChild(idx_);

    NodeIdx right_sibling = cfg_->nodes[idx_]->right_sibling;
    if (right_sibling == -1)
        return false;

    idx_ = right_sibling;
    return true;
}

// ----------------------------------------------------------------------------------------------------

void Reader::print() const
{
//    std::cout << "POINTER: [ ";
//    for(unsigned int i = 0; i < ptr_.stack.size(); ++i)
//        std::cout << ptr_.stack[i] << " ";
//    std::cout << "]" << std::endl;
}

} // end namespace config

} // end namespace tue

