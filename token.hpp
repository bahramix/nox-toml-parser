#pragma once
#include <cstdint>
#include <string_view>

namespace nox::toml{
    enum class token_type{
        invalid,
        equals,
        bare,
        string,
        right_bracket,
        left_bracket,
        right_brace,
        left_brace,
        comma,
        dot,
        next_line,
        end_of_file
    };

    struct token{
        token_type type;
        std::string_view value;
        std::uint32_t line;
        std::uint32_t column;
    };
}