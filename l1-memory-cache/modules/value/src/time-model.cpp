#include "time-model.hpp"

namespace l1_memory_cache::models
{
    TimeModel::TimeModel(const Duration &ttl) : time_point_(std::chrono::system_clock::now() + ttl)
    {
    }
    TimeModel::TimePoint TimeModel::ExpiredTime() const
    {
        return time_point_;
    }
    bool TimeModel::IsExpired() const
    {
        return time_point_ < std::chrono::system_clock::now();
    }
    TimeModel::operator bool() const
    {
        return time_point_ >= std::chrono::system_clock::now();
    }
} // namespace l1_memory_cache::models