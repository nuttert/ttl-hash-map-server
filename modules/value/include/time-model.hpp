#pragma once
#include <chrono>

namespace l1_memory_cache::models
{

    class TimeModel
    {
    public:
        using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
        using Duration = std::chrono::milliseconds;
    public:
        TimeModel(const Duration &ttl);
        virtual TimePoint ExpiredTime() const;

        virtual bool IsExpired() const;
        virtual operator bool() const;

    protected:
        TimePoint time_point_;
    };
} // namespace l1_memory_cache::models
