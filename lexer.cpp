#include "lexer.hpp"
#include "token.hpp"
#include <fstream>
#include <iterator>
#include <iostream>

namespace nox::toml{
    lexer::lexer()
    : tokens(_tokens)
    , cursor(0)
    {}

    bool lexer::load_source(const std::string& path){
        std::ifstream file(path);
        if(!file.is_open() && !file.good()){
            return false;
        }

        source = std::string(std::istreambuf_iterator<char>{file}, std::istreambuf_iterator<char>{});

        return true;
    }

    char lexer::peek(){
        if(is_at_end()){
            return '\0';
        }

        return source[cursor];
    }

    char lexer::advance(){
        if(is_at_end()){
            return '\0';
        }

        char c = source[cursor];
        cursor++;

        return c;
    }

    void lexer::skip_white_space(){
        while(peek() == ' ' || peek() == '\t'){
            advance();
        }

        if(peek() == '#'){
            while(!is_at_end() && peek() != '\n'){
                advance();
            }
        }
    }

    bool lexer::is_at_end(){
        if(cursor >= source.size()){
            return true;
        }

        return false;
    }

    token lexer::next_token(){
        skip_white_space();
        
        char c = advance();

        switch(c){
            case '=':
                return {token_type::equals};
            case '[':
                return {token_type::right_bracket};
            case ']':
                return {token_type::left_bracket};
            case '{':
                return {token_type::right_brace};
            case '}':
                return {token_type::left_brace};
            case ',':
                return {token_type::comma};
            case '.':
                return {token_type::dot};
            case '\n':
                return {token_type::next_line};
            case '"':
                return read_string();
        }

        if(is_bare(c)){
            return read_bare();
        }

        return {token_type::invalid};
    }

    token lexer::read_string(){
        uint32_t start = cursor;

        while(!is_at_end() && peek() != '\n'){
            char c = advance();
            
            if(c == '"'){
                return {token_type::string, std::string_view(source.data() + start, cursor - 1 - start)};
            }
        }

        return {token_type::invalid, "unfinished string"};
    }

    token lexer::read_bare(){
        uint32_t start = cursor - 1;

        while(is_bare(peek())){
            advance();
        }

        return token{token_type::bare, std::string_view(source.data() + start, cursor - start)};
    }

    bool lexer::is_bare(char c){
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_') || (c == '-');
    }

    bool lexer::load_tokens(){
        while(!is_at_end()){
            _tokens.push_back(next_token());
        }

        return true;
    }

    void lexer::print_tokens(){
        for(const token& tk : tokens){
            if(tk.type == token_type::invalid){
                std::cout << "[invalid]\n";
            }
            else if(tk.type == token_type::equals){
                std::cout << "[equals]\n";
            }
            else if(tk.type == token_type::bare){
                std::cout << "[bare] -> " << tk.value << "\n";
            }
            else if(tk.type == token_type::string){
                std::cout << "[string] -> " << tk.value << "\n";
            }
            else if(tk.type == token_type::right_bracket){
                std::cout << "[right bracket]\n";
            }
            else if(tk.type == token_type::left_bracket){
                std::cout << "[left bracket]\n";
            }
            else if(tk.type == token_type::right_brace){
                std::cout << "[right brace]\n";
            }
            else if(tk.type == token_type::left_brace){
                std::cout << "[left brace]\n";
            }
            else if(tk.type == token_type::comma){
                std::cout << "[comma]\n";
            }
            else if(tk.type == token_type::dot){
                std::cout << "[dot]\n";
            }
            else if(tk.type == token_type::next_line){
                std::cout << "[next line]\n";
            }
            else{
                std::cout << "[end of file]\n";
            }
        }
    }
}
