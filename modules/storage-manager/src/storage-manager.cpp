#include "storage-manager.hpp"
#include <iostream>

namespace l1_memory_cache
{
    std::optional<StorageManager::ValueType> StorageManager::Get(const KeyType &key) const
    {
        std::shared_lock<Mutex> lock(mutex_);
        auto it = map_.find(key);
        if (it == map_.end())
            return std::nullopt;
        StorageManager::ValueType value = it->second;
        return value;
    }

    std::vector<std::optional<StorageManager::ValueType>> StorageManager::Get(const std::vector<KeyType> &keys) const
    {
        std::shared_lock<Mutex> lock(mutex_);
        std::vector<Optional<ValueType>> values;
        values.reserve(keys.size());

        for (const auto &key : keys)
        {
            auto it = map_.find(key);
            if (it == map_.end())
                values.push_back(std::nullopt);
            else
                values.push_back(it->second);
        }
        return values;
    }
    void StorageManager::Set(const KeyType &key, const ValueType &value)
    {
        std::lock_guard<Mutex> lock(mutex_);
        auto [iterator, inserted] = map_.insert({key, value});

        if (!inserted)
            iterator->second = value;
    }
    void StorageManager::Set(const KeyType &key, ValueType &&value)
    {
        std::lock_guard<Mutex> lock(mutex_);
        auto [iterator, inserted] = map_.insert({key, std::move(value)});

        if (!inserted)
            iterator->second = std::move(value);
    }
    void StorageManager::Set(const Map &map)
    {
        std::lock_guard<Mutex> lock(mutex_);
        for (const auto &[key, value] : map)
        {
            auto [iterator, inserted] = map_.insert({key, value});

            if (!inserted)
                iterator->second = value;
        }
    }
    void StorageManager::Set(Map &&map)
    {
        std::lock_guard<Mutex> lock(mutex_);
        for (auto &&[key, value] : map)
        {
            auto [iterator, inserted] = map_.insert({key, std::move(value)});

            if (!inserted)
                iterator->second = std::move(value);
        }
    }

    size_t StorageManager::Del(const KeyType &key)
    {
        std::lock_guard<Mutex> lock(mutex_);
        return map_.erase(key);
    }
    size_t StorageManager::Del(const std::vector<KeyType> &keys)
    {
        std::lock_guard<Mutex> lock(mutex_);
        size_t amount = 0;
        for (const auto &key : keys)
            amount += map_.erase(key);

        return amount;
    }
    std::vector<StorageManager::KeyType> StorageManager::Keys()
    {
        std::shared_lock<Mutex> lock(mutex_);
        std::vector<KeyType> keys;
        keys.reserve(map_.size());

        for (const auto &[key, _] : map_)
            keys.push_back(key);
        return keys;
    }
} // namespace l1_memory_cache