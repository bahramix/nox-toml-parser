#include "../table.hpp"
#include <cstdint>
#include <iostream>

int main(){
    nox::toml::table t;
    nox::toml::table t1;
    nox::toml::table t2;
    nox::toml::table t3;

    t1["name"] = "fernando";
    t1["idade"] = 25;

    t["t1"] = t1;

    std::cout << t["t1"]["name"].as<std::string>() << std::endl;
}