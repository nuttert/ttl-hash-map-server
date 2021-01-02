#pragma once
#include <memory>
#include <string>
#include <functional>

#include "server-interface.hpp"

namespace evpp
{
    class EventLoop;
    class TCPServer;
    class TCPConn;
    class Buffer;
} // namespace evpp

namespace server
{
    class TCPServer : public TCPServerInterface
    {
    public:
        using ServerImpl = evpp::TCPServer;
        using EventLoopImpl = evpp::EventLoop;
        using CallbackOnMessage = std::function<void (const std::shared_ptr<evpp::TCPConn>, evpp::Buffer*)>;
        using CallbackOnConnection = std::function<void (const std::shared_ptr<evpp::TCPConn>)>;
    public:
        TCPServer(
            const CallbackOnMessage& callback_on_message, 
            const CallbackOnConnection& callback_on_connection, 
        const std::string& addr = "0.0.0.0:9099", size_t thread_num = 4);
        void Run() override;
        void Stop() override;
    private:
      std::shared_ptr<ServerImpl>  server_impl_ptr_;
      std::shared_ptr<EventLoopImpl>  event_loop_impl_ptr_;

     CallbackOnMessage callback_on_message_;
     CallbackOnConnection callback_on_connection_;
      std::string addr_;
      size_t thread_num_;
    };
} // namespace server