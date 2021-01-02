#pragma once
#include <memory>
namespace evpp
{
    class EventLoop;
    class TCPServer;
    class TCPConn;
    class Buffer;
} // namespace evpp

namespace l1_memory_cache
{
    class ServiceInterface
    {
    public:
        virtual ~ServiceInterface() = default;
        virtual void Run() = 0;
        virtual void Stop() = 0;

    protected:
        virtual void CallbackOnMessage(const std::shared_ptr<evpp::TCPConn>, evpp::Buffer *) = 0;
        virtual void CallbackOnConnection(const std::shared_ptr<evpp::TCPConn>) = 0;
    };
} // namespace l1_memory_cache