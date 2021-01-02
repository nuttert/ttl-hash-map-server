#include "storage-manager.hpp"
#include <iostream>

namespace l1_memory_cache
{
    StorageManager::Optional<StorageManager::ValueType &> StorageManager::Get(const KeyType &key)
    {
        std::shared_lock<Mutex> lock(mutex_);
        auto it = map_.find(key);
        if (it == map_.end())
            return boost::none;
        return it->second;
    }
    StorageManager::Optional<const StorageManager::ValueType &> StorageManager::Get(const KeyType &key) const
    {
        std::shared_lock<Mutex> lock(mutex_);
        auto it = map_.find(key);
        if (it == map_.end())
            return boost::none;
        return it->second;
    }

    std::vector<StorageManager::Optional<const StorageManager::ValueType &>> StorageManager::Get(const std::vector<KeyType> &keys) const
    {
        std::shared_lock<Mutex> lock(mutex_);
        std::vector<Optional<const ValueType &>> values{};

        for (const auto &key : keys)
        {
            auto it = map_.find(key);
            if (it == map_.end())
                values.push_back(boost::none);
            else
                values.push_back(it->second);
        }
        return values;
    }
    void StorageManager::Set(const KeyType &key, const ValueType &value)
    {
        std::shared_lock<Mutex> lock(mutex_);
        if(map_.find(key) != map_.end()) throw std::runtime_error("Key already exists");
        map_.insert({key, value});
    }
    void StorageManager::Set(const KeyType &key, ValueType &&value)
    {
        std::shared_lock<Mutex> lock(mutex_);
        if(map_.find(key) != map_.end()) throw std::runtime_error("Key already exists");
        map_.insert({key, std::move(value)});
    }
    void StorageManager::Set(const Map &map)
    {
        std::shared_lock<Mutex> lock(mutex_);
        for (const auto &[key, value] : map){
            if(map_.find(key) != map_.end()) throw std::runtime_error("Key already exists");
            map_.insert({key, value});
        }
    }
    void StorageManager::Set(Map &&map)
    {
        std::shared_lock<Mutex> lock(mutex_);
        for (const auto &[key, value] : map){
            if(map_.find(key) != map_.end()) throw std::runtime_error("Key already exists");
            map_.insert({key, std::move(value)});
        }
    }

    size_t StorageManager::Del(const KeyType &key)
    {
        std::shared_lock<Mutex> lock(mutex_);
        return map_.erase(key);
    }
    size_t StorageManager::Del(const std::vector<KeyType> &keys)
    {
        std::shared_lock<Mutex> lock(mutex_);
        size_t amount = 0;
        for (const auto &key : keys)
            amount += map_.erase(key);

        return amount;
    }
    std::vector<StorageManager::KeyType> StorageManager::Keys()
    {
        std::shared_lock<Mutex> lock(mutex_);
        std::vector<KeyType> keys{};
        for (const auto &[key, _] : map_)
            keys.push_back(key);
        return keys;
    }
} // namespace l1_memory_cache