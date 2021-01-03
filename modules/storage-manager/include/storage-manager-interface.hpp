#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "value.hpp"

namespace l1_memory_cache
{

    class StorageManagerInterface
    {
    public:
        using KeyType = std::string;
        using ValueType = models::Value;
        using Map = std::unordered_map<KeyType, models::Value>;

        template<typename T>
        using Optional = std::optional<T>;
    public:
        virtual Optional<ValueType> Get(const KeyType &key) const = 0;
        virtual std::vector<Optional<ValueType>> Get(const std::vector<KeyType> &keys) const = 0;

        virtual void Set(const KeyType &key, const ValueType &value) = 0;
        virtual void Set(const KeyType &key, ValueType &&value) = 0;
        virtual void Set(const Map&) = 0;
        virtual void Set(Map&&) = 0;

        virtual size_t Del(const KeyType &key) = 0;
        virtual size_t Del(const std::vector<KeyType>& keys) = 0;
        
        virtual std::vector<KeyType> Keys() = 0;
        virtual ~StorageManagerInterface() = default;
    };
} // namespace l1_memory_cache