#pragma once
#include <vector>
#include "table.hpp"
#include "token.hpp"

namespace nox::toml{
    class parser{
        private:
            table& _table;
            const std::vector<token>& tokens;

            token peek();
            token advance();
            bool is_at_end();

            bool parse_int();
            bool parse_double();
            bool parse_bool();
            bool parse_string();
            bool parse_table();
        
        public:
            const table& table;

            parser();
            
            const nox::toml::table& parse(const std::vector<token>& tokens);
    };
}