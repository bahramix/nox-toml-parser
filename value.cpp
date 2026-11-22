#include "value.hpp"
#include "table.hpp"
#include <stdexcept>
#include <utility>
#include <variant>

namespace nox::toml{
    value& value::operator[](const std::string& key){
        if(!std::holds_alternative<std::unique_ptr<table>>(data)){
            throw std::logic_error("cannot access non-table value");
        }

        auto& ptr = std::get<std::unique_ptr<table>>(data);

        return (*ptr)[key];
    }
    
    void value::operator=(std::variant<int64_t, double, bool, std::string, std::unique_ptr<table>>&& value){
        data = std::move(value);
    }

    void value::operator=(table& t){
        data = std::make_unique<table>(std::move(t));
    }
}