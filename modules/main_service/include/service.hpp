#pragma once
#include <memory>
#include <string>
#include <functional>
#include <iostream>

#include "config.hpp"
#include "service-interface.hpp"
#include "server-interface.hpp"
#include "key-value-container.hpp"
#include "parser-interface.hpp"

namespace l1_memory_cache
{
    class Service : public ServiceInterface
    {
        using Server = server::TCPServerInterface;
        using Parser = parser::ParserInterface;
    public:
        Service();

        void Run() override;
        void Stop() override;
    private:
        void CallbackOnMessage(const std::shared_ptr<evpp::TCPConn>, evpp::Buffer*) override;
        void CallbackOnConnection(const std::shared_ptr<evpp::TCPConn>) override;
    private:
        std::shared_ptr<Server> server_ptr_;
        std::shared_ptr<Parser> parser_ptr_;
        KeyValueContainer container_;
    };
} // namespace l1_memory_cache