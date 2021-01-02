#pragma once
#include <nlohmann/json.hpp>
#include <chrono>

namespace l1_memory_cache::models
{
    using Json = nlohmann::json;

    class BaseModel
    {
    public:
        virtual Json ToJson() const = 0;
        virtual void FromJson(const Json &json_obj) = 0;
    };
} // namespace l1_memory_cache::models
