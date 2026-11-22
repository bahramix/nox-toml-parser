#pragma once
#include <cstdint>
#include <memory>
#include <string>
#include <variant>

namespace nox::toml{
    struct table;
    struct value{
        std::variant<int64_t, double, bool, std::string, std::unique_ptr<table>> data;

        value& operator[](const std::string& key);
        void operator=(std::variant<int64_t, double, bool, std::string, std::unique_ptr<table>>&& value);
        void operator=(table& t);

        template <typename T>
        bool is(){
            return std::holds_alternative<T>(data);
        }

        template <typename T>
        T& as(){
            return std::get<T>(data);
        }
    };
}