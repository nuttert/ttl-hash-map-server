#pragma once
#include <concepts>
#include <string>
#include <optional>
#include <type_traits>
#include <variant>
#include <vector>
#include <shared_mutex>

#include "storage-manager-interface.hpp"

namespace l1_memory_cache
{
    class StorageManager: public StorageManagerInterface
    {
    public:
        using Mutex = std::shared_mutex;
    public:
        StorageManager() = default;

        Optional<const ValueType &> Get(const KeyType &key) const override;
        std::vector<Optional<const ValueType &>> Get(const std::vector<KeyType> &keys) const override;

        void Set(const KeyType &key, const ValueType &value) override;
        void Set(const KeyType &key, ValueType &&value) override;

        void Set(const Map& map) override;
        void Set(Map&& map) override;

        size_t Del(const KeyType &key) override;
        size_t Del(const std::vector<KeyType>& keys) override;

        std::vector<KeyType> Keys() override;

    private:
        Map map_;
        mutable  Mutex mutex_;
    };
} // namespace l1_memory_cache