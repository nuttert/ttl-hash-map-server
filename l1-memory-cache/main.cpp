#include <iostream>
#include <key-value-container.hpp>
#include <nlohmann/json.hpp>
#include <thread>
#include "server.hpp"
#include "service.hpp"

using namespace l1_memory_cache;


int main(){
    // auto obj = std::unordered_map<std::string, int>{
    //     {"a",5},  
    //     {"b", 6},
    // };

    // l1_memory_cache::KeyValueContainer container(std::chrono::milliseconds(999));
    // container.Set(obj);
    // // container.Set(obj);

    // std::cout << std::string(*container.Get("a")) << std::endl;
    l1_memory_cache::Service serv{};
    serv.Run();

    return 0;
}