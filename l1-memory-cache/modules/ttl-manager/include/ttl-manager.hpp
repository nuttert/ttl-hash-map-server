#pragma once
#include <queue>
#include <concepts>
#include <string>
#include <shared_mutex>
#include <type_traits>
#include <variant>
#include <vector>

#include "ttl-manager-interface.hpp"
#include "storage-manager-interface.hpp"
#include "worker-interface.hpp"

namespace l1_memory_cache
{
    class TTLManager : public TTLManagerInterface
    {
    public:
        using Queue = std::queue<std::string>;
        using Mutex = std::shared_mutex;

    public:
        TTLManager(const Duration &ttl, std::shared_ptr<StorageManagerInterface> storage_manager, std::shared_ptr<WorkerInterface> worker_ptr = nullptr);

        void SetTTL(const Duration &ttl) override;
        void PushKey(const QueueType &value) override;
        void PushKey(QueueType &&value) override;
        void PushKeys(const std::vector<QueueType> &value) override;
        void PushKeys(std::vector<QueueType> &&value) override;
        void PopKey() override;
        bool QueueIsEmpty() const override;
        QueueType GetKey() const override;

        void Callback() override;

        ~TTLManager();

    private:
        Duration ttl_;
        Queue queue_;
        mutable Mutex mutex_;

        std::shared_ptr<StorageManagerInterface> storage_manager_ptr_;
        std::shared_ptr<WorkerInterface> worker_ptr_;
    };
} // namespace l1_memory_cache