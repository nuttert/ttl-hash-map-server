#pragma once
#include <concepts>
#include <type_traits>
#include <variant>

//Values types
#include <vector>
#include <unordered_map>
#include <string>

#include <utils.hpp>

namespace l1_memory_cache::concepts{
    using namespace utils_interfaces;

    //64 bits, строка 40 бит => лишних 24 бита
    using ValueType = std::variant<
            std::unordered_map<std::string, std::string>,
            std::vector<std::string>,
            std::string>;
    
    template<typename T>
    concept Keyable = std::is_same_v<T, std::string>;

    template<typename T>
    concept Valueable = requires(T t){
            requires 
                std::is_same_v<T, std::string> ||
                Containerable<T> ||
                Mapable<T>;
    };
}