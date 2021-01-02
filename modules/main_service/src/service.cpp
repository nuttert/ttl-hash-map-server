#include "service.hpp"
#include "config.hpp"
#include "server.hpp"
#include "parser.hpp"

#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>

#include <nlohmann/json.hpp>
#include <iostream>

namespace
{
    template <typename OptionalType>
    std::string OptionalVectorToStr(const std::vector<OptionalType> &values)
    {
        if (values.size() == 1)
            return (values.front() ? std::string(*values.front()): "null");
        std::string values_str = "[";
        for (size_t i = 0; i < values.size(); ++i)
        {
            const auto &value = values[i];
            values_str += (value ? std::string(*value) : "null");
            if (i != values.size() - 1)
                values_str += ",";
        }
        values_str += "]";
        return values_str;
    }
} // namespace
namespace l1_memory_cache
{
    using Json = nlohmann::json;

    Service::Service() : container_(KeyValueContainer(config::ttl))
    {
        parser_ptr_ = std::make_shared<parser::Parser>();

        std::cout << "Server init started" << std::endl;
        server_ptr_ = std::make_shared<server::TCPServer>(
            [this](
                const std::shared_ptr<evpp::TCPConn> conn, evpp::Buffer *buffer) {
                CallbackOnMessage(conn, buffer);
            },
            [this](
                const std::shared_ptr<evpp::TCPConn> conn) {
                CallbackOnConnection(conn);
            },
            config::addr);
        std::cout << "Server init finished" << std::endl;
        std::cout << config::addr << std::endl;
    }
    void Service::Run()
    {
        server_ptr_->Run();
        std::cout << "Server started" << std::endl;
    }
    void Service::Stop()
    {
        server_ptr_->Stop();
    }

    void Service::CallbackOnMessage(const std::shared_ptr<evpp::TCPConn> conn, evpp::Buffer *buffer)
    {
        if (!conn || !parser_ptr_)
            return;

        auto parse_result = parser_ptr_->Parse(buffer->ToString());
        switch (parse_result.command)
        {
        case parser::ECommands::kSet:
        {
            try{
                for (const auto &[key, value] : parse_result.map)
                    container_.Set(parse_result.map);
            }catch(...){
                conn->Send("Key already exists");
            }
            break;
        }
        case parser::ECommands::kGet:
        {
            auto values = container_.Get(parse_result.vector);
            conn->Send(OptionalVectorToStr(values));
            break;
        }
        case parser::ECommands::kDel:
            container_.Del(parse_result.vector);
            break;
        case parser::ECommands::kKeys:
        {
            auto keys = container_.Keys();
            auto json_obj = Json(keys);
            conn->Send(json_obj.dump());
            break;
        }
        case parser::ECommands::kComandNotFoundError:
            conn->Send("Command Not Found");
            break;
        case parser::ECommands::kIsNotArrayOrStringError:
            conn->Send("Data is not array or string");
            break;
        case parser::ECommands::kIsNotKeyValueMapError:
            conn->Send("Data is not key-value map");
            break;
        case parser::ECommands::kParseError:
            conn->Send("Parse error");
            break;
        case parser::ECommands::kKeyError:
            conn->Send("Key error");
            break;
        default:
            conn->Send("Error");
            break;
        }
        conn->Send("\n>> ");
        buffer->Reset();
    }
    void Service::CallbackOnConnection(const std::shared_ptr<evpp::TCPConn> conn)
    {
        if (!conn)
            return;
        std::cout << "New connection" << std::endl;
        conn->Send("New connection \n");
        conn->Send("TTL: " + std::to_string(config::ttl.count()) + " milliseconds");
        conn->Send("\n>> ");
    }
} // namespace l1_memory_cache