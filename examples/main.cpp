#include "../parser.hpp"
#include "../lexer.hpp"

int main(){
    nox::toml::lexer lx;
    nox::toml::parser ps;

    lx.load_source("/examples/sample.toml");
    lx.load_tokens();

    nox::toml::table t = ps.parse(lx.tokens);

    t["compiler"]["version"].as<std::string>();
}