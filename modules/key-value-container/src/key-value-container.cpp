#include "key-value-container.hpp"
#include "storage-manager.hpp"
#include "ttl-manager.hpp"

namespace l1_memory_cache
{
    KeyValueContainer::KeyValueContainer(const Duration &ttl,
                                         std::shared_ptr<StorageManagerInterface> storage_manager_ptr,
                                         std::shared_ptr<TTLManagerInterface> ttl_manager_ptr) : ttl_(ttl),
                                                                                                 storage_manager_ptr_(storage_manager_ptr), ttl_manager_ptr_(ttl_manager_ptr)

    {
        if (!storage_manager_ptr)
            storage_manager_ptr_ = std::make_shared<StorageManager>();
        if (!ttl_manager_ptr)
            ttl_manager_ptr_ = std::make_shared<TTLManager>(ttl, storage_manager_ptr_);
    }

    void KeyValueContainer::SetTTL(const Duration &ttl)
    {
        ttl_ = ttl;
        ttl_manager_ptr_->SetTTL(ttl);
    }
    std::optional<KeyValueContainer::ValueType> KeyValueContainer::Get(const KeyType &key) const
    {
        const auto &storage = *storage_manager_ptr_;
        const auto value = storage.Get(key);
        if (value)
            return value;
        return std::nullopt;
    }
    std::vector<KeyValueContainer::Optional<KeyValueContainer::ValueType>> KeyValueContainer::Get(const std::vector<KeyType> &keys) const{
        const auto &storage = *storage_manager_ptr_;
        const auto values = storage.Get(keys);
        return values;
    }
    size_t KeyValueContainer::Del(const KeyType &key)
    {
        return storage_manager_ptr_->Del(key);
    }
    size_t KeyValueContainer::Del(const std::vector<KeyType> &keys){
         return storage_manager_ptr_->Del(keys);
    }
    std::vector<KeyValueContainer::KeyType> KeyValueContainer::Keys()
    {
        return storage_manager_ptr_->Keys();
    }
} // namespace l1_memory_cache