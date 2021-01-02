#pragma once

namespace server
{
    class TCPServerInterface
    {
    public:
        virtual ~TCPServerInterface() = default;
        virtual void Run() = 0;
        virtual void Stop() = 0;
    };
} // namespace server