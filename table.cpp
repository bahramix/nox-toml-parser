#include "table.hpp"

namespace nox::toml{
    value& table::operator[](const std::string& key){
        return entries[key];
    }
}