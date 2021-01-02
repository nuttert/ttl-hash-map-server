#pragma once
#include <string>
#include <vector>
#include <chrono>

namespace l1_memory_cache
{
    class TTLManagerInterface
    {
    public:
        using QueueType = std::string;
        using Duration = std::chrono::milliseconds;

    public:
        virtual ~TTLManagerInterface() = default;
        virtual void SetTTL(const Duration &ttl) = 0;
        virtual void PushKey(const QueueType &value) = 0;
        virtual void PushKey(QueueType &&value) = 0;
        virtual void PushKeys(const std::vector<QueueType> &value) = 0;
        virtual void PushKeys(std::vector<QueueType> &&value) = 0;
        virtual void PopKey() = 0;
        virtual bool QueueIsEmpty() const = 0;
        virtual QueueType GetKey() const = 0;

        virtual void Callback() = 0;
    };
} // namespace l1_memory_cache