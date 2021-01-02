#pragma once
#include <string>
#include <unordered_map>

#include "base-model.hpp"
#include "time-model.hpp"

namespace l1_memory_cache::models
{
    using Json = nlohmann::json;

    class Value : public BaseModel, public TimeModel
    {
    public:
        using Map = std::unordered_map<std::string, Value>;

    public:
        Value(const char *value, const Duration &ttl);
        Value(const std::string &value, const Duration &ttl);
        Value(std::string &&value, const Duration &ttl);
        template <typename T>
        Value(const T &value, const Duration &ttl);
        template <typename T>
        Value(T &&value, const Duration &ttl);

        operator std::string() const;

        const std::string &Get() const;
        Json ToJson() const override;
        void FromJson(const Json &json_obj) override;

    private:
        std::string value_{};
    };
} // namespace l1_memory_cache::models

namespace l1_memory_cache::models
{
    template <typename T>
    Value::Value(const T &value, const Duration &ttl): TimeModel(ttl)
    {
        Json json_obj = value;
        value_ = json_obj.dump();
    }
    template <typename T>
    Value::Value(T &&value, const Duration &ttl): TimeModel(ttl)
    {
        Json json_obj = std::forward<T>(value);
        value_ = json_obj.dump();
    }
} // namespace l1_memory_cache::models