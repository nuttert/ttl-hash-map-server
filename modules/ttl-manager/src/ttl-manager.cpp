#include <ttl-manager.hpp>
#include <worker.hpp>
#include <iostream>

namespace l1_memory_cache
{
    TTLManager::TTLManager(
        const Duration &ttl,
        std::shared_ptr<StorageManagerInterface> storage_manager_ptr,
        std::shared_ptr<WorkerInterface> worker_ptr) : ttl_(ttl), storage_manager_ptr_(storage_manager_ptr), worker_ptr_(worker_ptr)
    {
        if (!storage_manager_ptr)
            throw std::runtime_error("Storage manager is nullptr");
        if (!worker_ptr)
            worker_ptr_ = std::make_shared<Worker>([this]() {
                Callback();
            },
                                                   ttl);
        worker_ptr_->Run();
    }

    void TTLManager::SetTTL(const Duration &ttl)
    {
        ttl_ = ttl;
    }
    void TTLManager::PushKey(const QueueType &value)
    {
        std::lock_guard<Mutex> lock(mutex_);
        queue_.push(value);
    }
    void TTLManager::PushKey(QueueType &&value)
    {
        std::lock_guard<Mutex> lock(mutex_);
        queue_.push(std::move(value));
    }
    void TTLManager::PushKeys(const std::vector<QueueType> &values)
    {
        std::lock_guard<Mutex> lock(mutex_);
        for (const auto &value : values)
            queue_.push(value);
    }
    void TTLManager::PushKeys(std::vector<QueueType> &&values)
    {
        std::lock_guard<Mutex> lock(mutex_);
        for (auto &&value : values)
            queue_.push(std::move(value));
    }
    void TTLManager::PopKey()
    {
        std::lock_guard<Mutex> lock(mutex_);
        queue_.pop();
    }
    TTLManager::QueueType TTLManager::GetKey() const
    {
        std::shared_lock<Mutex> lock(mutex_);
        return queue_.front();
    }
    bool TTLManager::QueueIsEmpty() const
    {
        return queue_.empty();
    }

    void TTLManager::Callback()
    {
        std::vector<QueueType> expired_keys;

        while (!queue_.empty())
        {
            const auto &key = GetKey();
            const auto &value_opt = storage_manager_ptr_->Get(key);

            if (!value_opt)
            {
                PopKey();
                continue;
            }

            if (value_opt->IsExpired())
            {
                expired_keys.push_back(key);
                PopKey();
            }
            else
                break;
        }

        if (!expired_keys.empty())
        {
            storage_manager_ptr_->Del(expired_keys);
        }
    }

    TTLManager::~TTLManager()
    {
        worker_ptr_->Stop();
    }
} // namespace l1_memory_cache