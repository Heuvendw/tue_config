#include "tue/config2/yaml_emitter.h"
#include "tue/config2/configuration.h"
#include "tue/config2/node.h"

#include "tue/config2/map.h"
#include "tue/config2/sequence.h"

namespace tue
{
namespace config
{

// ----------------------------------------------------------------------------------------------------

YAMLEmitter::YAMLEmitter()
{
}

// ----------------------------------------------------------------------------------------------------

void emitRecursive(std::ostream& out, const tue::config::Configuration& cfg, const NodePtr& n,
                   const std::string& indent, bool ignore_first_indent = false)
{
    if (n->type() == ARRAY)
    {
        Sequence* array = static_cast<Sequence*>(n.get());
        const std::vector<NodeIdx>& children = array->children_;
        for(std::vector<NodeIdx>::const_iterator it = children.begin(); it != children.end(); ++it)
        {
            out << indent << "- ";
            emitRecursive(out, cfg, cfg.nodes[*it], indent + "  ", true);
        }
    } else
    {
        Map* map = static_cast<Map*>(n.get());

        const std::map<Label, Variant>& values = map->values;
        for(std::map<Label, Variant>::const_iterator it = values.begin(); it != values.end(); ++it)
        {
            if (!ignore_first_indent)
                out << indent;
            else
                ignore_first_indent = false;

            out << cfg.getName(it->first) << ": " << it->second << std::endl;
        }

        const std::map<Label, NodeIdx>& children = map->map_;
        for(std::map<Label, NodeIdx>::const_iterator it = children.begin(); it != children.end(); ++it)
        {
            if (!ignore_first_indent)
                out << indent;
            else
                ignore_first_indent = false;

            out << cfg.getName(it->first) << ": " << std::endl;
            emitRecursive(out, cfg, cfg.nodes[it->second], indent + "    ");
        }
    }
}

// ----------------------------------------------------------------------------------------------------

void YAMLEmitter::emit(const tue::config::Configuration& cfg, std::ostream& out, const std::string& indent)
{
    emitRecursive(out, cfg, cfg.nodes[0], indent);
}

} // end namespace config

} // end namespace tue

