#include "value.hpp"


namespace l1_memory_cache::models{
    using Json = nlohmann::json;
    
    Value::Value(const std::string &value, const Duration &ttl): TimeModel(ttl), value_(value){}
    Value::Value(std::string &&value, const Duration &ttl): TimeModel(ttl), value_(std::move(value)){}
    Value::Value(const char *value, const Duration &ttl): TimeModel(ttl), value_(value){}

     Value::operator std::string() const{
        return value_;  
     }

    const std::string& Value::Get() const{
        return value_;
    }
    Json Value::ToJson() const{
        return Json::parse(value_);
    }
    void Value::FromJson(const Json& json_obj){
        value_ = json_obj.dump();
    }  
}