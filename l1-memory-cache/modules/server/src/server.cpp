#include "server.hpp"
#include <evpp/tcp_server.h>
#include <evpp/buffer.h>
#include <evpp/tcp_conn.h>

namespace server
{
    TCPServer::TCPServer(
        const CallbackOnMessage &callback_on_message,
        const CallbackOnConnection &callback_on_connection,
        const std::string &addr, size_t thread_num) : callback_on_message_(callback_on_message), callback_on_connection_(callback_on_connection), addr_(addr), thread_num_(thread_num)
    {
        event_loop_impl_ptr_ = std::make_shared<EventLoopImpl>();
        server_impl_ptr_ = std::make_shared<ServerImpl>(event_loop_impl_ptr_.get(), addr, "TCPServer", thread_num);

        server_impl_ptr_->SetMessageCallback(callback_on_message);
        server_impl_ptr_->SetConnectionCallback(callback_on_connection);
    }
    void TCPServer::Run()
    {
        server_impl_ptr_->Init();
        server_impl_ptr_->Start();
        event_loop_impl_ptr_->Run();
    }
    void TCPServer::Stop()
    {
         event_loop_impl_ptr_->Stop();
         server_impl_ptr_->Stop();
    }
} // namespace server