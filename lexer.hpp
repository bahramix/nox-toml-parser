#pragma once
#include "token.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace nox::toml{
    class lexer{
        private:
            std::string source;
            uint32_t cursor;
            std::vector<token> _tokens;

            char peek();
            char advance();
            void skip_white_space();
            bool is_at_end();
            token next_token();

            token read_string();
            token read_bare();

            bool is_bare(char c);

        public:
            const std::vector<token>& tokens;

            lexer();
            bool load_source(const std::string& path);
            bool load_tokens();
            void print_tokens();
    };
}
