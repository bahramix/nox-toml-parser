#include "../lexer.hpp"

int main(){
    nox::toml::lexer lexer;
    lexer.load_source("examples/sample.toml");
    lexer.load_tokens();
    lexer.print_tokens();
}