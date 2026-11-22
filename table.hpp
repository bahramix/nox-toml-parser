#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include "value.hpp"

namespace nox::toml{
    struct table{
        std::unordered_map<std::string, value> entries;

        value& operator[](const std::string& key);
    };
}