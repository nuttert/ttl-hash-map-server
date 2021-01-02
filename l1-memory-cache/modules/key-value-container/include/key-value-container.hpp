#pragma once
#include <concepts>
#include <chrono>
#include <string>
#include <memory>
#include <variant>
#include <vector>
#include <type_traits>
// Boost optional поскольку он поддерживает ссылки, а std::optional нет
#include <boost/optional/optional.hpp>

#include "storage-manager-interface.hpp"
#include "ttl-manager-interface.hpp"

#include "utils.hpp"

namespace l1_memory_cache
{
    using namespace utils_interfaces;

    class KeyValueContainer
    {
    public:
        using KeyType = StorageManagerInterface::KeyType;
        using ValueType = StorageManagerInterface::ValueType;
        using Map = StorageManagerInterface::Map;
        using Duration = ValueType::Duration;
        template<typename T>
        using Optional = StorageManagerInterface::Optional<T>;
    public:
        KeyValueContainer(const Duration &ttl,
                          std::shared_ptr<StorageManagerInterface> storage_manager = nullptr,
                          std::shared_ptr<TTLManagerInterface> ttl_manager = nullptr);
        void SetTTL(const Duration &ttl);

        Optional<const ValueType &> Get(const KeyType &key) const;
        std::vector<Optional<const ValueType &>> Get(const std::vector<KeyType> &keys) const;

        template <typename T>
        void Set(const KeyType &key, const T &value);
        template <typename T>
        void Set(const KeyType &key, T &&value);
        template <typename T>
        void Set(const std::unordered_map<KeyType, T>& map);
        template <typename T>
        void Set(std::unordered_map<KeyType, T>&& map);

        size_t Del(const std::vector<KeyType> &keys);
        size_t Del(const KeyType &key);
        
        std::vector<KeyType> Keys();

    private:
        //Применим идиому PIMPL, но это отразится на скорости в рантайме из-за указателей. С другой стороны,
        //Мы можем позволить себе модульное тестирование, тетсировать один модуль и мокать остальные за счет интерфейсов и указателей.
        //Альтернативный подход FastPipml. В реальных проектах, где важна скорость я бы использовал подход с последним.
        std::shared_ptr<StorageManagerInterface> storage_manager_ptr_;
        std::shared_ptr<TTLManagerInterface> ttl_manager_ptr_;

        Duration ttl_;
    };
} // namespace l1_memory_cache

namespace l1_memory_cache
{
    template <typename T>
    void KeyValueContainer::Set(const KeyType &key, const T &value)
    {
        storage_manager_ptr_->Set(key, ValueType(value, ttl_));
        ttl_manager_ptr_->PushKey(key);
    }
    template <typename T>
    void KeyValueContainer::Set(const KeyType &key, T &&value)
    {
        storage_manager_ptr_->Set(key, ValueType(std::forward<T>(value), ttl_));
        ttl_manager_ptr_->PushKey(key);
    }
    template <typename T>
    void KeyValueContainer::Set(const std::unordered_map<KeyType, T>& map){
        Map key_value_map{};
        std::vector<KeyType> keys;

        for(const auto& [key, value]: map){
            key_value_map.insert({key, ValueType(value, ttl_)});
            keys.push_back(key);
        }
        storage_manager_ptr_->Set(std::move(key_value_map));
        ttl_manager_ptr_->PushKeys(std::move(keys));
    }
    template <typename T>
    void KeyValueContainer::Set(std::unordered_map<KeyType, T>&& map){
        Map key_value_map{};
        std::vector<KeyType> keys;

        for(auto&& [key, value]: map){
            key_value_map.insert({std::move(key), ValueType(std::move(value), ttl_)});
            keys.push_back(key);
        }
        storage_manager_ptr_->Set(std::move(key_value_map));
        ttl_manager_ptr_->PushKeys(std::move(keys));
    }
} // namespace l1_memory_cache